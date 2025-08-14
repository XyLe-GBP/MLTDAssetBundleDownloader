// PROGRESSDLG.cpp : 実装ファイル
//

#include "pch.h"
#include "MLTDABD.h"
#include "PROGRESSDLG.h"
#include "afxdialogex.h"
#include "MLTDABDDlg.h"
#include "MLTDABD.common.h"


// PROGRESSDLG ダイアログ
UINT m_nTimerID;
CString PROGRESSDLG::m_ErrorMsg = _T("");

IMPLEMENT_DYNAMIC(PROGRESSDLG, CDialogEx)

PROGRESSDLG::PROGRESSDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROGRESSDIALOG, pParent)
	, m_strAccum()
{
	CUR_POS = 0;
	MAX_POS = 0;
	POS = _T("");
	MAX = _T("");
	PROGRESSTEXT = _T("");
	hDCBackBuffer = NULL;
	hDCStatic = NULL;
	m_Hbrush = NULL;
}

PROGRESSDLG::~PROGRESSDLG()
{
}

void PROGRESSDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_MAIN, xv_Progress);
	//DDX_Control(pDX, IDC_STATIC_LOG, m_Static);
}


BEGIN_MESSAGE_MAP(PROGRESSDLG, CDialogEx)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &PROGRESSDLG::OnBnClickedButtonCancel)
	ON_MESSAGE(WM_PROCESS_FINISHED, &PROGRESSDLG::OnProcessFinished)
	ON_MESSAGE(WM_APPEND_TEXT, &PROGRESSDLG::OnAppendText)
END_MESSAGE_MAP()

// PROGRESSDLG メッセージ ハンドラー

BOOL PROGRESSDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UINT timerID = 1;
	UINT interval = 1 * 1000;

	m_nTimerID = SetTimer(timerID, interval, NULL);

	m_Static.SubclassDlgItem(IDC_STATIC_LOG, this);
	m_strAccum.Empty();
	m_Static.SetWindowText(_T(""));

	xv_Progress.SetMarquee(TRUE, 30);
	SetDlgItemText(IDC_STATIC, _T("処理中です。しばらくお待ちください…"));
	SetDlgItemText(IDC_STATIC_LOG, _T("Processing..."));

	return TRUE;
}

void PROGRESSDLG::OnBnClickedButtonCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	INT_PTR ret = MessageBox(_T("処理を中止しようとしています。\n中止した場合、現在の処理内容は失われます。続行しますか？"), _T("警告"), MB_ICONWARNING | MB_YESNO);
	if (ret == IDYES) {
		::SetEvent(CMLTDABDDlg::m_hCancelEvent);
		CMLTDABDDlg::SuspendFlag = 1;
		EndDialog(IDOK);
		return;
	}
	else {
		return;
	}
}

BOOL PROGRESSDLG::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return FALSE;

		case VK_ESCAPE:
			return FALSE;

		default:
			break;
		}
	}

	if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4) return(TRUE);

	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT PROGRESSDLG::OnAppendText(WPARAM wParam, LPARAM lParam)
{
	LPWSTR pwsz = reinterpret_cast<LPWSTR>(lParam);
	CString chunk(pwsz);
	OutputDebugString(chunk);
	//delete[] pwsz;

	// 累積してから、一気に SetWindowText
	//m_strAccum += chunk;
	//m_Static.SetWindowText(m_strAccum);

	m_Static.SetWindowText(chunk);
	m_Static.Invalidate(FALSE);
	m_Static.UpdateWindow();

	return 0;
}

LRESULT PROGRESSDLG::OnProcessFinished(WPARAM wParam, LPARAM lParam)
{
	// モーダルダイアログを閉じる
	EndDialog(IDOK);
	return 0;
}

void PROGRESSDLG::UpdateProgressText()
{
	switch (CMLTDABDDlg::ProgressThreadFlag)
	{
		case 0: // DownloadProc
		{
			SetWindowText(_T("WorkerThread:[ダウンロード処理中]"));
			break;
		}
		case 1: // ShapingProc
		{
			SetWindowText(_T("WorkerThread:[整形処理中]"));
			break;
		}
		case 2: // MainShapingProc
		{
			SetWindowText(_T("WorkerThread:[整形および最終処理中]"));
			break;
		}
		case 255:
		{
			SetWindowText(_T("スレッドが開始されていません"));
			break;
		}
		default: // Other(none)
		{
			break;
		}
	}

	m_Static.Invalidate(FALSE);
	m_Static.UpdateWindow();
	/*HDC hdc;
	PAINTSTRUCT ps;

	OutputDebugString(CMLTDABDDlg::m_hRet);
	POS.Format(_T("アップスケーリング中： %u ファイル /"), CUR_POS);
	MAX.Format(_T(" %u ファイル"), MAX_POS);
	PROGRESSTEXT = POS + MAX;

	SetWindowText(PROGRESSTEXT);
	OutputDebugString(PROGRESSTEXT + _T("\n"));
	::SetBkColor(hDCStatic, RGB(240, 240, 240));
	::SelectObject(hDCBackBuffer, hDCStatic);
	m_Hbrush = (HBRUSH)::SelectObject(hDCBackBuffer, CreateSolidBrush(RGB(240, 240, 240)));
	::PatBlt(hDCBackBuffer, 0, 0, rc.right, rc.bottom, PATCOPY);
	::SelectObject(hDCBackBuffer, m_Hbrush);
	::DrawText(hDCStatic, PROGRESSTEXT, -1, &rc, DT_RIGHT | DT_NOCLIP | DT_SINGLELINE);
	this->m_Static.InvalidateRect(rc, 0);
	hdc = ::BeginPaint(this->m_Static, &ps);
	::BitBlt(hdc, 0, 0, rc.right, rc.bottom, hDCBackBuffer, 0, 0, SRCCOPY);
	::EndPaint(this->m_Static, &ps);
	this->m_Static.UpdateWindow();*/
}

void PROGRESSDLG::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (nIDEvent == m_nTimerID) {
		INT cur{}, max{};

		//xv_Progress.GetRange(cur, max);
		//xv_Progress.SetPos(CMLTDABDDlg::PROGRESS_COUNT);
		UpdateProgressText();

		if (CMLTDABDDlg::SuspendFlag == 1) {
			PostMessage(WM_CLOSE);
			return;
		}
		/*if (static_cast<UINT>(max) <= CMLTDABDDlg::PROGRESS_COUNT) {
			PostMessage(WM_CLOSE);
			return;
		}*/
		if (CMLTDABDDlg::ExceptionFlag == 1) {
			m_ErrorMsg = _T("Exception error has occured.");
			PostMessage(WM_CLOSE);
			return;
		}
	}
	if (nIDEvent == m_nTimerID) {
		ValueFlag = CUR_POS;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void PROGRESSDLG::OnDestroy()
{
	if (CMLTDABDDlg::m_pWorkerThread && CMLTDABDDlg::m_hCancelEvent) { ::SetEvent(CMLTDABDDlg::m_hCancelEvent); ::WaitForSingleObject(CMLTDABDDlg::m_pWorkerThread->m_hThread, 2000); } 
	// イベントクローズ（一度だけ)
	if (CMLTDABDDlg::m_hCancelEvent) { ::CloseHandle(CMLTDABDDlg::m_hCancelEvent); CMLTDABDDlg::m_hCancelEvent = nullptr; }

	CDialogEx::OnDestroy();

	//KillTimer(m_TimerID);
	KillTimer(m_nTimerID);
	//m_TimerID = 0;
	m_nTimerID = 0;
	if (hDCStatic) { ::ReleaseDC(this->m_Static, hDCStatic); hDCStatic = NULL; }
	if (hDCBackBuffer) { ::DeleteDC(hDCBackBuffer); hDCBackBuffer = NULL; }
}