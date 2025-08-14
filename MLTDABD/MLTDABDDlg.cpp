
// MLTDABDDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MLTDABD.h"
#include "MLTDABDDlg.h"
#include "afxdialogex.h"

#include "MLTDABD.common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "PROGRESSDLG.h"

#define SAFE_FREE(ptr) { free(ptr); ptr = NULL; }
#define SAFE_DELETE(ptr) { delete ptr; ptr = NULL; }
#define WM_MYMSG (WM_APP + 1)

// リードスレッド停止用のメッセージID
#define WM_USER_READ_TERMINATE (WM_USER + 100)

HANDLE CMLTDABDDlg::m_hCancelEvent;
CWinThread* CMLTDABDDlg::m_pWorkerThread;

CComboBox CMLTDABDDlg::m_hCmbUabRes;

UINT CMLTDABDDlg::ProgressThreadFlag = 255;
UINT CMLTDABDDlg::SuspendFlag = 0;
UINT CMLTDABDDlg::PROGRESS_COUNT = 0;
UINT CMLTDABDDlg::ExceptionFlag = 0;
DWORD CMLTDABDDlg::m_hLastError;

CString CMLTDABDDlg::m_hRet;
CString CMLTDABDDlg::m_hSavePath = _T("");
CString CMLTDABDDlg::m_hDLURI = _T("");
CString CMLTDABDDlg::m_hShapedFilePath = _T("");
CString CMLTDABDDlg::m_hDownloadMsg = _T("Downloading: ");
TCHAR* CMLTDABDDlg::m_hSavepathT;

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual BOOL OnInitDialog();

// 実装
protected:
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticHyper1();
	afx_msg void OnStnClickedStaticHyper2();
	afx_msg void OnStnClickedStaticIcon();
	CStatic VersionText;
	CStatic m_hyper1, m_hyper2, m_hIcon;
	COLORREF m_hyperlink;
	CFont m_hlfont;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	m_hyperlink = NULL;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VERSIONTEXT, VersionText);
	DDX_Control(pDX, IDC_STATIC_HYPER1, m_hyper1);
	DDX_Control(pDX, IDC_STATIC_HYPER2, m_hyper2);
	DDX_Control(pDX, IDC_STATIC_ICON, m_hIcon);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	ON_STN_CLICKED(IDC_STATIC_HYPER1, &CAboutDlg::OnStnClickedStaticHyper1)
	ON_STN_CLICKED(IDC_STATIC_HYPER2, &CAboutDlg::OnStnClickedStaticHyper2)
	ON_STN_CLICKED(IDC_STATIC_ICON, &CAboutDlg::OnStnClickedStaticIcon)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->VersionText.SetWindowText(APP_VER());
	m_hyperlink = RGB(0, 0, 255);
	CFont* pFont = m_hyper1.GetFont();
	LOGFONT lFont;
	pFont->GetLogFont(&lFont);
	lFont.lfUnderline = (TRUE);
	m_hlfont.CreateFontIndirect(&lFont);
	m_hyper1.SetFont(&m_hlfont, TRUE);
	m_hyper2.SetFont(&m_hlfont, TRUE);

	return TRUE;
}

BOOL CAboutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (pWnd == &this->m_hyper1)
	{
		HCURSOR CURSOR_CUR = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR1));
		::SetCursor(CURSOR_CUR);
		return TRUE;
	}
	if (pWnd == &this->m_hyper2)
	{
		HCURSOR CURSOR_CUR = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR1));
		::SetCursor(CURSOR_CUR);
		return TRUE;
	}
	if (pWnd == &this->m_hIcon)
	{
		HCURSOR CURSOR_CUR = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR1));
		::SetCursor(CURSOR_CUR);
		return TRUE;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd == &this->m_hyper1) {
		pDC->SetTextColor(m_hyperlink);
	}
	if (pWnd == &this->m_hyper2) {
		pDC->SetTextColor(m_hyperlink);
	}
	return hbr;
}


void CAboutDlg::OnStnClickedStaticHyper1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	ShellExecute(NULL, _T("open"), _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x78\x79\x6c\x65\x2d\x6f\x66\x66\x69\x63\x69\x61\x6c\x2e\x63\x6f\x6d"), NULL, NULL, SW_SHOWNORMAL);
}


void CAboutDlg::OnStnClickedStaticHyper2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	ShellExecute(NULL, _T("open"), _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x67\x69\x74\x68\x75\x62\x2e\x63\x6f\x6d\x2f\x58\x79\x4c\x65\x2d\x47\x42\x50\x2f\x4d\x4c\x54\x44\x41\x73\x73\x65\x74\x42\x75\x6e\x64\x6c\x65\x44\x6f\x77\x6e\x6c\x6f\x61\x64\x65\x72"), NULL, NULL, SW_SHOWNORMAL);
}


void CAboutDlg::OnStnClickedStaticIcon()
{
	std::random_device rnd;
	UINT RND = rnd();
	if (RND < 0x7FFFFFFF) {
		if (RND <= 0x3B9AC9FF) {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_HRK_DOM), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			MessageBox(_T("ドームですよっ！ドームっ！"), _T("ammhrkさん"), MB_ICONMASK | MB_OK);
			return;
		}
		else {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_HRK_PRD), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			MessageBox(_T("プロデューサーさんっ！悪用厳禁ですよっ、悪用厳禁っ！"), _T("ammhrkさん"), MB_ICONMASK | MB_OK);
			return;
		}
	}
	if (RND > 0x80000000) {
		if (RND > 0xA0000000) {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_HRK_DDR), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			MessageBox(_T("えっ？だっ、誰？"), _T("ammhrkさん"), MB_ICONMASK | MB_OK);
			return;
		}
		else {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_HRK_PRD), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			MessageBox(_T("プロデューサーさんっ！ツールですよっ、ツールっ！"), _T("ammhrkさん"), MB_ICONMASK | MB_OK);
			return;
		}
	}
}


void CAboutDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}


// CMLTDABDDlg ダイアログ

IMPLEMENT_DYNAMIC(CMLTDABDDlg, CDialogEx)

CMLTDABDDlg::CMLTDABDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MLTDABD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_ML);
}

CMLTDABDDlg::~CMLTDABDDlg(){}

void CMLTDABDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VERSION, m_hCmbAssetVer);
	DDX_Control(pDX, IDC_STATIC_HASH, m_hStatic_Hash);
	DDX_Control(pDX, IDC_STATIC_UPDATE_DATE, m_hStatic_Date);
	DDX_Control(pDX, IDC_COMBO_UABRES, m_hCmbUabRes);
}

static UINT AFX_CDECL ABDownloadWorkThreadProc(LPVOID pParam)
{
	PROGRESSDLG* pDlg = reinterpret_cast<PROGRESSDLG*>(pParam);
	HANDLE hCancel = CMLTDABDDlg::m_hCancelEvent;
	if (hCancel && ::WaitForSingleObject(hCancel, 0) == WAIT_OBJECT_0) {
		pDlg->SendMessage(WM_PROCESS_FINISHED, 0, 0);
		return 0;
	}

	// ── ここで重い処理を実行 ──

	CMLTDABDDlg::ProgressThreadFlag = 0;
	Sleep(4000);
	pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(CStringToLPWSTR(CMLTDABDDlg::m_hDownloadMsg)));
	
	while (!DownloadFile(CMLTDABDDlg::m_hDLURI, CMLTDABDDlg::m_hSavePath, 1024)) {
		// キャンセルが要求されていたら即終了
		if (hCancel && ::WaitForSingleObject(hCancel, 0) == WAIT_OBJECT_0)
			goto CLEANUP;
	}
	//pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(L"Download Completed."));
	//Sleep(2000);

	if (CMLTDABDDlg::SuspendFlag == 1) {
		CMLTDABDDlg::ProgressThreadFlag = 255;
		pDlg->SendMessage(WM_PROCESS_FINISHED, 0, 0);
		return 0;
	}
	else {
		// 処理完了をダイアログに通知（UI スレッド側で EndDialog を呼ぶ）
		pDlg->SendMessage(WM_PROCESS_FINISHED, 0, 0);
	}
	
	CMLTDABDDlg::ProgressThreadFlag = 255;
	return 0;

CLEANUP:
	CMLTDABDDlg::SuspendFlag = 1;
	pDlg->SendMessage(WM_PROCESS_FINISHED, 0, 0);
	CMLTDABDDlg::ProgressThreadFlag = 255;
	return 0;
}

static UINT AFX_CDECL ShapingWorkThreadProc(LPVOID pParam)
{
	PROGRESSDLG* pDlg = reinterpret_cast<PROGRESSDLG*>(pParam);
	HANDLE hCancel = CMLTDABDDlg::m_hCancelEvent;
	if (hCancel && ::WaitForSingleObject(hCancel, 0) == WAIT_OBJECT_0) {
		pDlg->SendMessage(WM_PROCESS_FINISHED, 0, 0);
		return 0;
	}

	// ── ここで重い処理を実行 ──

	CMLTDABDDlg::ProgressThreadFlag = 1;

	// パイプ作成（標準出力 → 読み取り用 hRead）
	SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };
	HANDLE hRead = NULL, hWrite = NULL;
	if (!::CreatePipe(&hRead, &hWrite, &sa, 0)) {
		OutputDebugString(_T("CreatePipe Error."));
		CMLTDABDDlg::ExceptionFlag = 1;
		goto DONE;
	}

	// 読み取りハンドルは継承しない
	::SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0);

	// STARTUPINFO 設定（ハンドル継承 & 非表示）
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.hStdOutput = hWrite;
	si.hStdError = hWrite;
	si.wShowWindow = SW_HIDE;

	TCHAR cmdLine[256];
	_tcscpy_s(cmdLine, _countof(cmdLine), CMLTDABDDlg::m_hSavepathT);

	// CREATE_NO_WINDOW でコンソールを非表示に起動
	if (!::CreateProcess(
		NULL,            // アプリ名
		cmdLine,		 // コマンドライン
		NULL, NULL,      // セキュリティ属性
		TRUE,            // ハンドル継承
		CREATE_NO_WINDOW,// プロセス作成フラグ
		NULL,            // 環境
		NULL,            // カレントディレクトリ
		&si, &pi))
	{
		DWORD err = ::GetLastError();
		CMLTDABDDlg::m_hLastError = err;
		CString errMsg;
		errMsg.Format(_T("CreateProcess failed with error %u\r\n"), err);
		// 失敗メッセージをダイアログに追記
		LPWSTR buf = new WCHAR[errMsg.GetLength() + 1];
		wcscpy_s(buf, static_cast<rsize_t>(errMsg.GetLength()) + 1, errMsg);
		pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(buf));

		::CloseHandle(hWrite);
		::CloseHandle(hRead);
		CMLTDABDDlg::ExceptionFlag = 1;
		goto DONE;
	}

	// 不要な書き込みハンドルをクローズ
	::CloseHandle(hWrite);

	// パイプからの読み取りループ
	const DWORD BUFSIZE = 4096;
	CHAR  buffer[BUFSIZE]{};
	DWORD bytesRead = 0;
	while (::ReadFile(hRead, buffer, BUFSIZE - 1, &bytesRead, NULL) && bytesRead)
	{
		// キャンセルが要求されていたら即終了
		if (hCancel && ::WaitForSingleObject(hCancel, 0) == WAIT_OBJECT_0)
			goto CLEANUP;

		buffer[bytesRead] = '\0';

		// ANSI→Unicode + 改行コード変換
		CString chunk;
		{
			// MultiByteToWideChar で変換
			int n = ::MultiByteToWideChar(CP_ACP, 0, buffer, -1, NULL, 0);
			WCHAR* wbuf = new WCHAR[n];
			::MultiByteToWideChar(CP_ACP, 0, buffer, -1, wbuf, n);
			chunk = wbuf;
			delete[] wbuf;
		}
		chunk.Replace(_T("\n"), _T("\r\n"));

		// ダイアログに追記をポスト
		int len = chunk.GetLength() + 1;
		WCHAR* heapBuf = new WCHAR[len];
		wcscpy_s(heapBuf, len, static_cast<LPCTSTR>(chunk));
		pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(heapBuf));
	}

	::CloseHandle(hRead);

	// プロセス終了待ち
	::WaitForSingleObject(pi.hProcess, INFINITE);
	::CloseHandle(pi.hProcess);
	::CloseHandle(pi.hThread);

	if (CMLTDABDDlg::SuspendFlag == 1) {
		CMLTDABDDlg::ProgressThreadFlag = 255;
		pDlg->PostMessage(WM_PROCESS_FINISHED, 0, 0);
		return 0;
	}
	else {
		goto DONE;
	}

DONE:
	// ダイアログを閉じる
	pDlg->PostMessage(WM_PROCESS_FINISHED, 0, 0);
	CMLTDABDDlg::ProgressThreadFlag = 255;
	return 0;
CLEANUP:
	::CloseHandle(hRead);
	::WaitForSingleObject(pi.hProcess, INFINITE);
	::CloseHandle(pi.hProcess);
	::CloseHandle(pi.hThread);
	CMLTDABDDlg::SuspendFlag = 1;
	pDlg->SendMessage(WM_PROCESS_FINISHED, 0, 0);
	CMLTDABDDlg::ProgressThreadFlag = 255;
	return 0;
}

static UINT AFX_CDECL MainShapingWorkThreadProc(LPVOID pParam)
{
	PROGRESSDLG* pDlg = reinterpret_cast<PROGRESSDLG*>(pParam);
	HANDLE hCancel = CMLTDABDDlg::m_hCancelEvent;
	if (hCancel && ::WaitForSingleObject(hCancel, 0) == WAIT_OBJECT_0) {
		pDlg->SendMessage(WM_PROCESS_FINISHED, 0, 0);
		return 0;
	}

	// ── ここで重い処理を実行 ──
	CMLTDABDDlg::ProgressThreadFlag = 2;
	Sleep(4000);
	
	//pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(L"ifstream..."));

	std::ifstream fin(CMLTDABDDlg::m_hShapedFilePath);
	if (!fin) {
		CMLTDABDDlg::ExceptionFlag = 1;
		pDlg->PostMessage(WM_PROCESS_FINISHED, 0, 0);
		return -1;
	}

	pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(L"execute ifstream and ofstream..."));
	Sleep(2000);

	std::ofstream fout(".\\uabm.abddata");
	if (!fout) {
		CMLTDABDDlg::ExceptionFlag = 1;
		pDlg->PostMessage(WM_PROCESS_FINISHED, 0, 0);
		return -1;
	}

	std::string ss;

	pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(L"Final shaping and added..."));
	Sleep(2000);

	while (std::getline(fin, ss, '\n')) {
		if (hCancel && ::WaitForSingleObject(hCancel, 0) == WAIT_OBJECT_0)
			goto CLEANUP;

		CString RET;
		RET = ss.c_str();
		int pos = 0, npos = 0;
		std::string buf;
		CString RESNAME, INDEX; //AFH; // AFH is Options

		std::vector<size_t> findVec1 = find_all(ss, "\"resource\": ");
		std::vector<size_t> findVec2 = find_all(ss, "\"index\": ");

		for (const auto& pos : findVec1) {
			size_t ps = pos + 12, ds = ss.find(",") - 12;
			CString BUF;
			buf = ss.substr(ps, ds);
			AfxReplaceStr(buf, " ", "");
			AfxReplaceStr(buf, "0event", "event");
			AfxReplaceStr(buf, "zsong", "song");
			AfxReplaceStr(buf, "zevent", "event");
			AfxReplaceStr(buf, "z016", "016");
			AfxReplaceStr(buf, "z007", "007");
			AfxReplaceStr(buf, "yoffer", "offer");
			AfxReplaceStr(buf, "yicon", "icon");
			AfxReplaceStr(buf, "yevent", "event");
			AfxReplaceStr(buf, "ycb_", "cb_");
			AfxReplaceStr(buf, "yachievement", "achievement");
			AfxReplaceStr(buf, "y032", "032");
			AfxReplaceStr(buf, "xmain", "main");
			AfxReplaceStr(buf, "xex4c", "ex4c");
			AfxReplaceStr(buf, "xambi", "ambi");
			AfxReplaceStr(buf, "x015", "015");
			AfxReplaceStr(buf, "wsystem", "system");
			AfxReplaceStr(buf, "wstudent", "student");
			AfxReplaceStr(buf, "wstage2d", "stage2d");
			AfxReplaceStr(buf, "wsong3", "song3");
			AfxReplaceStr(buf, "wsong", "song");
			AfxReplaceStr(buf, "wscrobj", "scrobj");
			AfxReplaceStr(buf, "wbirth", "birth");
			AfxReplaceStr(buf, "wachievement", "achievement");
			fout << buf << ",";
			BUF = buf.c_str();
			CMLTDABDDlg::m_hCmbUabRes.AddString(BUF);
			//pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(CStringToLPWSTR(BUF)));
			break;
		}

		for (const auto& pos : findVec2) {
			size_t ps = pos + 10, ds = ss.find(",") - 10;
			CString BUF;
			buf = ss.substr(ps, ds);
			fout << buf << "\n";
			BUF = buf.c_str();
			pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(CStringToLPWSTR(BUF)));
			break;
		}
	}

	pDlg->SendMessage(WM_APPEND_TEXT, 0, reinterpret_cast<LPARAM>(L"Completed."));
	Sleep(2000);

	if (CMLTDABDDlg::SuspendFlag == 1) {
		CMLTDABDDlg::ProgressThreadFlag = 255;
		pDlg->PostMessage(WM_PROCESS_FINISHED, 0, 0);
		return 0;
	}
	else {
		// 処理完了をダイアログに通知（UI スレッド側で EndDialog を呼ぶ）
		pDlg->PostMessage(WM_PROCESS_FINISHED, 0, 0);
	}

	CMLTDABDDlg::ProgressThreadFlag = 255;
	return 0;

CLEANUP:
	CMLTDABDDlg::SuspendFlag = 1;
	pDlg->SendMessage(WM_PROCESS_FINISHED, 0, 0);
	CMLTDABDDlg::ProgressThreadFlag = 255;
	return 0;
}

BEGIN_MESSAGE_MAP(CMLTDABDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_COMMAND(ID_32771, &CMLTDABDDlg::OnAboutMLTDABD)
	ON_COMMAND(ID_32773, &CMLTDABDDlg::OnUpdateCheck)
	ON_BN_CLICKED(IDC_RADIO_PRT_ANDROID, &CMLTDABDDlg::OnBnClickedRadioPrtAndroid)
	ON_BN_CLICKED(IDC_RADIO_PRT_IOS, &CMLTDABDDlg::OnBnClickedRadioPrtIos)
	ON_CBN_SELCHANGE(IDC_COMBO_VERSION, &CMLTDABDDlg::OnCbnSelchangeComboVersion)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CMLTDABDDlg::OnBnClickedButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_BUNDLEINFO_UPDATE, &CMLTDABDDlg::OnBnClickedButtonBundleinfoUpdate)
	ON_BN_CLICKED(IDC_RADIO_SRV_ORIGINAL, &CMLTDABDDlg::OnBnClickedRadioSrvOriginal)
	ON_BN_CLICKED(IDC_RADIO_SRV_MIRROR, &CMLTDABDDlg::OnBnClickedRadioSrvMirror)
	ON_CBN_SELCHANGE(IDC_COMBO_UABRES, &CMLTDABDDlg::OnCbnSelchangeComboUabres)
	ON_BN_CLICKED(IDC_BUTTON_UABDOWNLOAD, &CMLTDABDDlg::OnBnClickedButtonUabdownload)
END_MESSAGE_MAP()


// CMLTDABDDlg メッセージ ハンドラー

BOOL CMLTDABDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	CFileFind find;

	if (find.FindFile(_T(".\\uabmr.exe"))) {
		wchar_t ver[20]{}, date[30]{}, index[50]{};
		GetPrivateProfileString(_T("MLTD_BUNDLE"), _T("0x0001"), NULL, (LPWSTR)ver, 20, _T(".\\settings.ini"));
		GetPrivateProfileString(_T("MLTD_BUNDLE"), _T("0x0002"), NULL, (LPWSTR)date, 30, _T(".\\settings.ini"));
		GetPrivateProfileString(_T("MLTD_BUNDLE"), _T("0x0003"), NULL, (LPWSTR)index, 50, _T(".\\settings.ini"));
		UINT flag, prt, srv;
		flag = GetPrivateProfileInt(_T("MLTD_BUNDLE"), _T("0x0000"), INFINITE, _T(".\\settings.ini"));
		prt = GetPrivateProfileInt(_T("MLTD_PLATFORM"), _T("0x0000"), INFINITE, _T(".\\settings.ini"));
		srv = GetPrivateProfileInt(_T("MLTD_SERVER"), _T("0x0000"), INFINITE, _T(".\\settings.ini"));
		if (prt == 0) {
			CheckRadioButton(IDC_RADIO_PRT_ANDROID, IDC_RADIO_PRT_IOS, IDC_RADIO_PRT_ANDROID);
		}
		if (prt == 1) {
			CheckRadioButton(IDC_RADIO_PRT_ANDROID, IDC_RADIO_PRT_IOS, IDC_RADIO_PRT_IOS);
		}
		else {
			WritePrivateProfileString(_T("MLTD_PLATFORM"), _T("0x0000"), _T("0"), _T(".\\settings.ini"));
			CheckRadioButton(IDC_RADIO_PRT_ANDROID, IDC_RADIO_PRT_IOS, IDC_RADIO_PRT_ANDROID);
		}

		if (srv == 0) {
			CheckRadioButton(IDC_RADIO_SRV_ORIGINAL, IDC_RADIO_SRV_MIRROR, IDC_RADIO_SRV_ORIGINAL);
		}
		if (srv == 1) {
			CheckRadioButton(IDC_RADIO_SRV_ORIGINAL, IDC_RADIO_SRV_MIRROR, IDC_RADIO_SRV_MIRROR);
		}
		else {
			WritePrivateProfileString(_T("MLTD_SERVER"), _T("0x0000"), _T("0"), _T(".\\settings.ini"));
			CheckRadioButton(IDC_RADIO_SRV_ORIGINAL, IDC_RADIO_SRV_MIRROR, IDC_RADIO_SRV_ORIGINAL);
		}

		m_hCancelEvent = ::CreateEvent(nullptr, TRUE, FALSE, nullptr);
		m_pWorkerThread = nullptr;

		return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
	}
	else {
		MessageBox(_T("'uabmr.exe' が見つかりません。\nアプリケーションを終了します。"), _T("必須ファイルが見つかりません"), MB_ICONERROR | MB_OK);
		EndDialog(IDCANCEL);
		PostMessage(WM_COMMAND, IDCANCEL);
		return FALSE;
	}
}

void CMLTDABDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMLTDABDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMLTDABDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMLTDABDDlg::OnAboutMLTDABD()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OutputDebugString(_T("OnAboutMLTDABD\n"));
	CAboutDlg About;
	About.DoModal();
}


void CMLTDABDDlg::OnUpdateCheck()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OutputDebugString(_T("OnUpdatecheck\n"));
	CString LatestVersion = AppUpdateCheck();
	if (LatestVersion == _T("")) {
		MessageBox(_T("情報取得中にエラーが発生しました。\nインターネット接続がされているか確認してください。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	if (LatestVersion == _T("-1")) {
		MessageBox(_T("情報取得中にエラーが発生しました。\nサーバーにデータが見つかりません。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	CString CurrentVersion = AppCurrentVersionCheck();
	if (CurrentVersion == _T("")) {
		MessageBox(_T("情報取得中にエラーが発生しました。\nインターネット接続がされているか確認してください。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	LatestVersion = LatestVersion.Left(CurrentVersion.GetLength());
	LatestVersion += _T("\r");
	if (LatestVersion == CurrentVersion + _T("\r")) {
		MessageBox(_T("最新バージョン：") + LatestVersion + _T("現在使用中のバージョン：") + CurrentVersion + _T("\nアプリケーションのバージョンは最新です。"), _T("完了"), MB_ICONINFORMATION | MB_OK);
		return;
	}
	else if (LatestVersion > CurrentVersion) {
		UINT ret;
		ret = MessageBox(_T("最新バージョン：") + LatestVersion + _T("現在使用中のバージョン：") + CurrentVersion + _T("\nアプリケーションのアップデートが可能です。サイトを開きますか？"), _T("アップデート確認"), MB_ICONINFORMATION | MB_YESNOCANCEL);
		if (ret == IDYES) {
			ShellExecute(NULL, _T("open"), _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x67\x69\x74\x68\x75\x62\x2e\x63\x6f\x6d\x2f\x58\x79\x4c\x65\x2d\x47\x42\x50\x2f\x4d\x4c\x54\x44\x41\x73\x73\x65\x74\x42\x75\x6e\x64\x6c\x65\x44\x6f\x77\x6e\x6c\x6f\x61\x64\x65\x72"), NULL, NULL, SW_SHOWNORMAL);
			return;
		}
		else if (ret == IDNO) {
			return;
		}
		else if (ret == IDCANCEL) {
			MessageBox(_T("キャンセルされました。"), _T("キャンセル"), MB_ICONWARNING | MB_OK);
		}
		else {
			return;
		}
	}
	else {
		MessageBox(_T("情報取得中にエラーが発生しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
}


void CMLTDABDDlg::OnBnClickedRadioPrtAndroid()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnBnClickedRadioPrtAndroid\n"));
	WritePrivateProfileString(_T("MLTD_PLATFORM"), _T("0x0000"), _T("0"), _T(".\\settings.ini"));
}


void CMLTDABDDlg::OnBnClickedRadioPrtIos()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnBnClickedRadioPrtIos\n"));
	WritePrivateProfileString(_T("MLTD_PLATFORM"), _T("0x0000"), _T("1"), _T(".\\settings.ini"));
}


void CMLTDABDDlg::OnBnClickedRadioSrvOriginal()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnBnClickedRadioSrvOriginal\n"));
	WritePrivateProfileString(_T("MLTD_SERVER"), _T("0x0000"), _T("0"), _T(".\\settings.ini"));
}


void CMLTDABDDlg::OnBnClickedRadioSrvMirror()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnBnClickedRadioSrvMirror\n"));
	WritePrivateProfileString(_T("MLTD_SERVER"), _T("0x0000"), _T("1"), _T(".\\settings.ini"));
}


void CMLTDABDDlg::OnCbnSelchangeComboVersion()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnCbnSelchangeComboVersion\n"));
	CButton* Button = (CButton*)GetDlgItem(IDC_BUTTON_DOWNLOAD);
	if (m_hCmbAssetVer.GetCurSel() != CB_ERR) {
		int cmbindexcount = m_hCmbAssetVer.GetCount(), cmbcurcount = m_hCmbAssetVer.GetCurSel(), lp = 0;
		std::ifstream fin(_T(".\\spd.abddata"));
		if (!fin) {
			Button->EnableWindow(FALSE);
			MessageBox(_T("予期せぬエラーが発生しました。\n(ファイルを開くことが出来ません。)"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}

		std::string ss;

		while (std::getline(fin, ss, '\n')) {
			if (lp == cmbcurcount) {
				size_t ind1 = ss.find(","), ind2 = ss.find("="), ind3 = ss.rfind("="), verlength = 0;
				std::string b1, b2, b3;
				b1 = ss.substr(0, ind1);
				verlength = b1.length();
				b2 = ss.substr(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(verlength) + 1, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(ind2) - verlength - 2);
				b3 = ss.substr(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(ind2) + 2, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(ind3) + 18 - verlength);
				CString Ver, Index, Date;
				Ver = b1.c_str(), Date = b2.c_str(), Index = b3.c_str();
				m_hStatic_Hash.SetWindowText(Index);
				m_hStatic_Date.SetWindowText(Date);
				WritePrivateProfileString(_T("MLTD_MANIFEST"), _T("0x0001"), Ver, _T(".\\settings.ini"));
				WritePrivateProfileString(_T("MLTD_MANIFEST"), _T("0x0002"), Date, _T(".\\settings.ini"));
				WritePrivateProfileString(_T("MLTD_MANIFEST"), _T("0x0003"), Index, _T(".\\settings.ini"));
				OutputDebugString(_T("AssetBundle Manifest version: ") + Ver + _T("\n"));
				OutputDebugString(_T("AssetBundle Manifest release date: ") + Date + _T("\n"));
				OutputDebugString(_T("AssetBundle Manifest index: ") + Index +_T("\n"));
			}
			lp++;
		}
		Button->EnableWindow(TRUE);
	}
	else {
		Button->EnableWindow(FALSE);
	}
}


void CMLTDABDDlg::OnBnClickedButtonDownload()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnBnClickedButtonDownload\n"));
	wchar_t ver[20]{}, index[50]{};
	UINT prt, srv, veri;
	prt = GetPrivateProfileInt(_T("MLTD_PLATFORM"), _T("0x0000"), INFINITE, _T(".\\settings.ini"));
	srv = GetPrivateProfileInt(_T("MLTD_SERVER"), _T("0x0000"), INFINITE, _T(".\\settings.ini"));
	veri = GetPrivateProfileInt(_T("MLTD_MANIFEST"), _T("0x0001"), INFINITE, _T(".\\settings.ini"));
	GetPrivateProfileString(_T("MLTD_MANIFEST"), _T("0x0001"), NULL, (LPWSTR)ver, 20, _T(".\\settings.ini"));
	GetPrivateProfileString(_T("MLTD_MANIFEST"), _T("0x0003"), NULL, (LPWSTR)index, 50, _T(".\\settings.ini"));
	CFileFind find;
	CString SAVEPATH, OS, SERVER, VER = ver, INDEX = index, UNITYVER;
	CString filter("Unity AssetBundle Manifest (*.data, *.unity3d)|*.data;*.unity3d|テキストファイル (*.txt)|*.txt||");
	CFileDialog selDlg(FALSE, _T("data"), _T("MLTD-UABM-VERSION-") + VER, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, filter, this);
	selDlg.m_ofn.lpstrTitle = (_T("Unity AssetBundle Manifestの保存"));
	if (prt == 0) {
		OS = _T("Android/");
	}
	else if (prt == 1) {
		OS = _T("iOS/");
	}
	else {
		OS = _T("Android/");
	}
	if (srv == 0) {
		SERVER = _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x64\x32\x73\x66\x34\x77\x39\x62\x6b\x76\x34\x38\x35\x63\x2e\x63\x6c\x6f\x75\x64\x66\x72\x6f\x6e\x74\x2e\x6e\x65\x74\x2f");
	}
	else if (srv == 1) {
		SERVER = _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x74\x64\x2d\x61\x73\x73\x65\x74\x73\x2e\x62\x6e\x37\x36\x35\x2e\x63\x6f\x6d\x2f");
	}
	else {
		SERVER = _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x64\x32\x73\x66\x34\x77\x39\x62\x6b\x76\x34\x38\x35\x63\x2e\x63\x6c\x6f\x75\x64\x66\x72\x6f\x6e\x74\x2e\x6e\x65\x74\x2f");
	}
	if (veri > 115990) {
		UNITYVER = _T("2018/");
	}
	else if (veri <= 14575) {
		UNITYVER = _T("");
		MessageBox(_T("このバージョンのUABMはダウンロードできません。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	else if (veri <= 115990) {
		UNITYVER = _T("2017.3/");
	}
	INT_PTR ret = selDlg.DoModal();
	if (ret == IDOK) {

		PROGRESSDLG waitDlg(this);

		// ワーカースレッドの起動（サスペンド状態で生成）
		m_pWorkerThread = AfxBeginThread(
			ABDownloadWorkThreadProc,
			&waitDlg,
			THREAD_PRIORITY_NORMAL,
			0,
			CREATE_SUSPENDED);

		SAVEPATH = selDlg.GetPathName();
		if (find.FindFile(SAVEPATH)) {
			DeleteFile(SAVEPATH);
		}
		wchar_t Drive[MAX_PATH]{}, Dir[MAX_PATH]{}, Name[MAX_PATH]{}, Ext[MAX_PATH]{};
		_tsplitpath_s(SAVEPATH, Drive, Dir, Name, Ext);
		CString DRIVE = Drive, DIR = Dir, NAME = Name, EXT = Ext;
		m_hSavePath = SAVEPATH;
		m_hDLURI = SERVER + VER + _T("/production/") + UNITYVER + OS + INDEX;
		m_hDownloadMsg = _T("Downloading:'version") + VER + _T("'...");

		// オートデリート設定（不要ならFALSEに）
		m_pWorkerThread->m_bAutoDelete = TRUE;
		m_pWorkerThread->ResumeThread();  // 実行開始

		// モーダル表示（内部で独自メッセージループが動く）
		waitDlg.DoModal();

		if (CMLTDABDDlg::SuspendFlag == 1) {
			CMLTDABDDlg::SuspendFlag = 0;
			MessageBox(_T("処理がキャンセルされました。"), _T("キャンセル"), MB_ICONWARNING | MB_OK);
			return;
		}
		if (CMLTDABDDlg::ExceptionFlag == 1) {
			CMLTDABDDlg::ExceptionFlag = 0;
			DWORD err = m_hLastError;
			CString str;
			str.Format(_T("エラーが発生しました。\n%u"), err);
			MessageBox((str), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}

		if (find.FindFile(SAVEPATH)) {
			if (223 >= GetFileSizeStat(SAVEPATH)) {
				DeleteFile(SAVEPATH);
				MessageBox(_T("ダウンロードに失敗しました。\nアクセスが拒否されました。"), _T("ダウンロードエラー"), MB_ICONERROR | MB_OK);
				return;
			}
			else if (223 < GetFileSizeStat(SAVEPATH)) {
				INT_PTR cf = MessageBox(_T("ダウンロードが完了しました。\n整形ツールで整形を行いますか？\n(整形を行わないと純正ファイルのまま保存され、UABのダウンロードは行えません)"), _T("UAB整形確認"), MB_ICONINFORMATION | MB_YESNO);
				if (cf != IDYES) {
					MessageBox(_T("保存が完了しました。"), _T("完了"), MB_ICONINFORMATION | MB_OK);
					ShellExecute(NULL, _T("open"), SAVEPATH.Left(SAVEPATH.ReverseFind('\\')), NULL, NULL, SW_SHOWNORMAL);
					return;
				}
				else {
					CString FP;
					TCHAR* savePathT = (TCHAR*)malloc(sizeof(TCHAR) * 512);
					if (NULL == savePathT) {
						perror("can not malloc");
						OutputDebugString(_T("TCHAR syntax (savePathT) malloc failed.\n"));
						return;
					}
					else {
						ZeroMemory(&savePathT[0], 512);
						if (EXT == ".data" || EXT == ".DATA") {
							_tcscpy_s(&savePathT[0], 512, _T("cmd.exe /c uabmr ") + SAVEPATH + _T(" -d ") + DRIVE + DIR + NAME + _T("_spd.data"));
							FP = DRIVE + DIR + NAME + _T("_spd.data");
						}
						else if (EXT == ".unity3d" || EXT == ".UNITY3D") {
							_tcscpy_s(&savePathT[0], 512, _T("cmd.exe /c uabmr ") + SAVEPATH + _T(" -d ") + DRIVE + DIR + NAME + _T("_spd.unity3d"));
							FP = DRIVE + DIR + NAME + _T("_spd.unity3d");
						}
						else if (EXT == ".txt" || EXT == ".TXT") {
							_tcscpy_s(&savePathT[0], 512, _T("cmd.exe /c uabmr ") + SAVEPATH + _T(" -d ") + DRIVE + DIR + NAME + _T("_spd.txt"));
							FP = DRIVE + DIR + NAME + _T("_spd.txt");
						}
						else {
							return; // Error
						}
					}

					m_hSavepathT = savePathT;
					m_hShapedFilePath = FP;

					// ワーカースレッドの起動（サスペンド状態で生成）
					m_pWorkerThread = AfxBeginThread(
						ShapingWorkThreadProc,
						&waitDlg,
						THREAD_PRIORITY_NORMAL,
						0,
						CREATE_SUSPENDED);

					// オートデリート設定（不要ならFALSEに）
					m_pWorkerThread->m_bAutoDelete = TRUE;
					m_pWorkerThread->ResumeThread();  // 実行開始

					// モーダル表示（内部で独自メッセージループが動く）
					waitDlg.DoModal();
					
					SAFE_FREE(savePathT);

					DeleteFile(SAVEPATH);

					if (CMLTDABDDlg::SuspendFlag == 1) {
						CMLTDABDDlg::SuspendFlag = 0;
						MessageBox(_T("処理がキャンセルされました。"), _T("キャンセル"), MB_ICONWARNING | MB_OK);
						return;
					}
					if (CMLTDABDDlg::ExceptionFlag == 1) {
						CMLTDABDDlg::ExceptionFlag = 0;
						DWORD err = m_hLastError;
						CString str;
						str.Format(_T("エラーが発生しました。\n%u"), err);
						MessageBox((str), _T("エラー"), MB_ICONERROR | MB_OK);
						return;
					}

					if (find.FindFile(FP)) {
						
						// ワーカースレッドの起動（サスペンド状態で生成）
						m_pWorkerThread = AfxBeginThread(
							MainShapingWorkThreadProc,
							&waitDlg,
							THREAD_PRIORITY_NORMAL,
							0,
							CREATE_SUSPENDED);

						// オートデリート設定（不要ならFALSEに）
						m_pWorkerThread->m_bAutoDelete = TRUE;
						m_pWorkerThread->ResumeThread();  // 実行開始

						// モーダル表示（内部で独自メッセージループが動く）
						waitDlg.DoModal();

						if (CMLTDABDDlg::SuspendFlag == 1) {
							CMLTDABDDlg::SuspendFlag = 0;
							MessageBox(_T("処理がキャンセルされました。"), _T("キャンセル"), MB_ICONWARNING | MB_OK);
							return;
						}
						if (CMLTDABDDlg::ExceptionFlag == 1) {
							CMLTDABDDlg::ExceptionFlag = 0;
							DWORD err = m_hLastError;
							CString str;
							str.Format(_T("エラーが発生しました。\n%u"), err);
							MessageBox((str), _T("エラー"), MB_ICONERROR | MB_OK);
							return;
						}

						MessageBox(_T("整形が完了しました。\nUABをダウンロードする場合は、下のコンボボックスから選択して\nダウンロードを行ってください。"), _T("完了"), MB_ICONINFORMATION | MB_OK);

						GetDlgItem(IDC_BUTTON_BUNDLEINFO_UPDATE)->EnableWindow(FALSE);
						GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE);
						m_hCmbAssetVer.EnableWindow(FALSE);
						m_hCmbUabRes.EnableWindow(TRUE);
						m_hCmbUabRes.SetCurSel(0);
						return;
					}
					else {
						MessageBox(_T("整形に失敗しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
						return;
					}
				}
			}
			else {
				return;
			}
		}
		else {
			MessageBox(_T("ダウンロードに失敗しました。\nインターネット接続を確認してください。"), _T("ダウンロードエラー"), MB_ICONERROR | MB_OK);
			return;
		}
	}
	else if (ret == IDCANCEL) {
		MessageBox(_T("キャンセルされました。"), _T("完了"), MB_ICONWARNING | MB_OK);
		return;
	}
	else {
		return;
	}
}


void CMLTDABDDlg::OnBnClickedButtonBundleinfoUpdate()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnBnClickedButtonBundleinfoUpdate\n"));
	CFileFind find;
	intptr_t ret = MessageBox(_T("アセットバンドル情報を更新しますか？\n(更新にはインターネット接続が必要です)"), _T("UAB更新確認"), MB_ICONWARNING | MB_YESNO);
	if (ret == IDYES) {
		DeleteFile(_T(".\\vsd.abddata"));
		DeleteFile(_T(".\\spd.abddata"));
		m_hCmbAssetVer.ResetContent();
		m_hStatic_Hash.SetWindowText(_T("データがありません"));
		m_hStatic_Date.SetWindowText(_T("データがありません"));

		PROGRESSDLG waitDlg(this);

		// ワーカースレッドの起動（サスペンド状態で生成）
		m_pWorkerThread = AfxBeginThread(
			ABDownloadWorkThreadProc,
			&waitDlg,
			THREAD_PRIORITY_NORMAL,
			0,
			CREATE_SUSPENDED);

		m_hSavePath = _T(".\\vsd.abddata");
		m_hDLURI = _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x61\x70\x69\x2e\x6d\x61\x74\x73\x75\x72\x69\x68\x69\x2e\x6d\x65\x2f\x6d\x6c\x74\x64\x2f\x76\x31\x2f\x76\x65\x72\x73\x69\x6f\x6e\x2f\x61\x73\x73\x65\x74\x73");
		m_hDownloadMsg = _T("Downloading: 'vsd'...");

		// オートデリート設定（不要ならFALSEに）
		m_pWorkerThread->m_bAutoDelete = TRUE;
		m_pWorkerThread->ResumeThread();  // 実行開始

		// モーダル表示（内部で独自メッセージループが動く）
		waitDlg.DoModal();

		if (CMLTDABDDlg::SuspendFlag == 1) {
			CMLTDABDDlg::SuspendFlag = 0;
			MessageBox(_T("処理がキャンセルされました。"), _T("キャンセル"), MB_ICONWARNING | MB_OK);
			return;
		}
		if (CMLTDABDDlg::ExceptionFlag == 1) {
			CMLTDABDDlg::ExceptionFlag = 0;
			DWORD err = m_hLastError;
			CString str;
			str.Format(_T("エラーが発生しました。\n%u"), err);
			MessageBox((str), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}

		if (find.FindFile(_T(".\\vsd.abddata"))) {

			std::ifstream fin(_T(".\\vsd.abddata"));
			if (!fin) {
				m_hCmbAssetVer.EnableWindow(FALSE);
				DeleteFile(_T(".\\vsd.abddata"));
				DeleteFile(_T(".\\spd.abddata"));
				MessageBox(_T("予期せぬエラーが発生しました。\n(ファイルを開くことが出来ません。)"), _T("UAB更新エラー"), MB_ICONERROR | MB_OK);
				return;
			}

			std::ofstream fout(_T(".\\spd.abddata"));
			if (!fout) {
				m_hCmbAssetVer.EnableWindow(FALSE);
				DeleteFile(_T(".\\vsd.abddata"));
				DeleteFile(_T(".\\spd.abddata"));
				MessageBox(_T("予期せぬエラーが発生しました。\n(ファイルを書き込むことが出来ません。)"), _T("UAB更新エラー"), MB_ICONERROR | MB_OK);
				return;
			}
			
			std::string ss;

			while (std::getline(fin, ss, '\n')) {
				CString RET;
				RET = ss.c_str();
				int pos = 0, npos = 0;
				std::string buf;
				CString VER, DATE, INDEX;

				std::vector<size_t> findVec1 = find_all(ss, "\"version\": ");
				std::vector<size_t> findVec2 = find_all(ss, "\"updateTime\": ");
				std::vector<size_t> findVec3 = find_all(ss, "\"indexName\": ");

				for (const auto& pos : findVec1) {
					size_t ps = pos + 11, ds = ss.find(",") - 15;
					CString VERBUF;
					buf = ss.substr(ps, ds);
					fout << buf << ",";
					VERBUF = buf.c_str();
					m_hCmbAssetVer.AddString(_T("UnityABM-") + VERBUF);
					break;
				}

				for (const auto& pos : findVec2) {
					size_t ps = pos + 15, ds = ss.find("\",") - 19;
					CString DATEBUF;
					buf = ss.substr(ps, ds);
					fout << buf << " = ";
					DATEBUF = buf.c_str();
					break;
				}

				for (const auto& pos : findVec3) {
					size_t ps = pos + 14, ds = ss.find_last_of("\"") - 18;
					CString INDEXBUF;
					buf = ss.substr(ps, ds);
					fout << buf << ";\n";
					INDEXBUF = buf.c_str();
					break;
				}
			}
			GetDlgItem(IDC_RADIO_PRT_ANDROID)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_PRT_IOS)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_SRV_ORIGINAL)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_SRV_MIRROR)->EnableWindow(FALSE);
			m_hCmbAssetVer.EnableWindow(TRUE);
			m_hCmbAssetVer.SetCurSel(0);
			DeleteFile(_T(".\\vsd.abddata"));
			MessageBox(_T("更新が完了しました。\nコンボボックスにてダウンロードしたいUABMを選択後、ダウンロードボタンを\n押下してください。"), _T("UAB更新完了"), MB_ICONINFORMATION | MB_OK);
			return;
		}
		else {
			m_hCmbAssetVer.EnableWindow(FALSE);
			MessageBox(_T("更新に失敗しました。\nインターネット接続を確認するか、時間を置いて再度実行してください。\n※短時間で複数回のアクセスを行うと、APIのアクセス制限が発生します。"), _T("UAB更新エラー"), MB_ICONERROR | MB_OK);
			return;
		}
	}
	else if (ret == IDNO) {
		return;
	}
	else {
		DeleteFile(_T(".\\vsd.abddata"));
		DeleteFile(_T(".\\spd.abddata"));
		m_hCmbAssetVer.ResetContent();
		m_hCmbAssetVer.EnableWindow(FALSE);
		m_hStatic_Hash.SetWindowText(_T("データがありません"));
		m_hStatic_Date.SetWindowText(_T("データがありません"));
		return;
	}
}


void CMLTDABDDlg::OnDestroy() {
	OutputDebugString(_T("OnDestroy\n"));
	if(m_pWorkerThread) {
		// もしまだ走っていたらキャンセル要求
		::SetEvent(m_hCancelEvent);
		::WaitForSingleObject(m_pWorkerThread->m_hThread, 2000);
	}
	if (m_hCancelEvent) {
		::CloseHandle(m_hCancelEvent);
		m_hCancelEvent = nullptr;
	}

	CDialogEx::OnDestroy();

	DeleteFile(_T(".\\vsd.abddata"));
	DeleteFile(_T(".\\spd.abddata"));
	DeleteFile(_T(".\\uabm.abddata"));
}


void CMLTDABDDlg::OnCbnSelchangeComboUabres()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnCbnSelchangeComboUabres\n"));
	CButton* Button = (CButton*)GetDlgItem(IDC_BUTTON_UABDOWNLOAD);
	if (m_hCmbUabRes.GetCurSel() != CB_ERR) {
		int cmbindexcount = m_hCmbUabRes.GetCount(), cmbcurcount = m_hCmbUabRes.GetCurSel(), lp = 0;
		std::ifstream fin(_T(".\\uabm.abddata"));
		if (!fin) {
			Button->EnableWindow(FALSE);
			MessageBox(_T("予期せぬエラーが発生しました。\n(ファイルを開くことが出来ません。)"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}

		string ss;
		wstring cbt_c;
		CString cbt;
		m_hCmbUabRes.GetLBText(m_hCmbUabRes.GetCurSel(), cbt);
		cbt_c = cbt;

		while (std::getline(fin, ss, '\n')) {
			size_t pos1 = ss.find(TWStringToString(cbt_c));
			if (pos1 != string::npos) {
				size_t ind1 = ss.find(","), ind2 = ss.find("="), length = 0;
				std::string b1, b2;
				b1 = ss.substr(0, ind1);
				length = b1.length();
				b2 = ss.substr(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(length) + 1, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(ind2) - length - 2);
				CString Res, Index;
				Res = b1.c_str(), Index = b2.c_str();
				m_hStatic_Hash.SetWindowText(Index);
				m_hStatic_Date.SetWindowText(_T("存在しません。"));
				WritePrivateProfileString(_T("MLTD_BUNDLE"), _T("0x0001"), Res, _T(".\\settings.ini"));
				WritePrivateProfileString(_T("MLTD_BUNDLE"), _T("0x0002"), Index, _T(".\\settings.ini"));
				OutputDebugString(_T("AssetBundle resource: ") + Res + _T("\n"));
				OutputDebugString(_T("AssetBundle index: ") + Index + _T("\n"));
			}
			/*if (lp == cmbcurcount) {
				size_t ind1 = ss.find(","), ind2 = ss.find("="), length = 0;
				std::string b1, b2;
				b1 = ss.substr(0, ind1);
				length = b1.length();
				b2 = ss.substr(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(length) + 1, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(ind2) - length - 2);
				CString Res, Index;
				Res = b1.c_str(), Index = b2.c_str();
				m_hStatic_Hash.SetWindowText(Index);
				m_hStatic_Date.SetWindowText(_T("存在しません。"));
				WritePrivateProfileString(_T("MLTD_BUNDLE"), _T("0x0001"), Res, _T(".\\settings.ini"));
				WritePrivateProfileString(_T("MLTD_BUNDLE"), _T("0x0002"), Index, _T(".\\settings.ini"));
				OutputDebugString(_T("AssetBundle resource: ") + Res + _T("\n"));
				OutputDebugString(_T("AssetBundle index: ") + Index + _T("\n"));
			}
			lp++;*/
		}
		Button->EnableWindow(TRUE);
	}
	else {
		Button->EnableWindow(FALSE);
	}
}


void CMLTDABDDlg::OnBnClickedButtonUabdownload()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnBnClickedButtonDownload\n"));
	wchar_t ver[20]{}, res[100]{}, index[50]{};
	UINT prt, srv, veri;
	prt = GetPrivateProfileInt(_T("MLTD_PLATFORM"), _T("0x0000"), INFINITE, _T(".\\settings.ini"));
	srv = GetPrivateProfileInt(_T("MLTD_SERVER"), _T("0x0000"), INFINITE, _T(".\\settings.ini"));
	veri = GetPrivateProfileInt(_T("MLTD_MANIFEST"), _T("0x0001"), INFINITE, _T(".\\settings.ini"));
	GetPrivateProfileString(_T("MLTD_MANIFEST"), _T("0x0001"), NULL, (LPWSTR)ver, 20, _T(".\\settings.ini"));
	GetPrivateProfileString(_T("MLTD_BUNDLE"), _T("0x0001"), NULL, (LPWSTR)res, 100, _T(".\\settings.ini"));
	GetPrivateProfileString(_T("MLTD_BUNDLE"), _T("0x0002"), NULL, (LPWSTR)index, 50, _T(".\\settings.ini"));
	CFileFind find;
	CString SAVEPATH, OS, SERVER, VER = ver, RES = res, INDEX = index, UNITYVER;
	CString filter("Unity AssetBundle (*.unity3d)|*.unity3d||");
	CFileDialog selDlg(FALSE, _T("unity3d"), RES, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, filter, this);
	selDlg.m_ofn.lpstrTitle = (_T("Unity AssetBundleの保存"));
	if (prt == 0) {
		OS = _T("Android/");
	}
	else if (prt == 1) {
		OS = _T("iOS/");
	}
	else {
		OS = _T("Android/");
	}
	if (srv == 0) {
		SERVER = _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x64\x32\x73\x66\x34\x77\x39\x62\x6b\x76\x34\x38\x35\x63\x2e\x63\x6c\x6f\x75\x64\x66\x72\x6f\x6e\x74\x2e\x6e\x65\x74\x2f");
	}
	else if (srv == 1) {
		SERVER = _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x74\x64\x2d\x61\x73\x73\x65\x74\x73\x2e\x62\x6e\x37\x36\x35\x2e\x63\x6f\x6d\x2f");
	}
	else {
		SERVER = _T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x64\x32\x73\x66\x34\x77\x39\x62\x6b\x76\x34\x38\x35\x63\x2e\x63\x6c\x6f\x75\x64\x66\x72\x6f\x6e\x74\x2e\x6e\x65\x74\x2f");
	}
	if (veri > 115990) {
		UNITYVER = _T("2018/");
	}
	else if (veri <= 14575) {
		UNITYVER = _T("");
		MessageBox(_T("このバージョンのUABはダウンロードできません。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	else if (veri <= 115990) {
		UNITYVER = _T("2017.3/");
	}
	INT_PTR ret = selDlg.DoModal();
	if (ret == IDOK) {

		PROGRESSDLG waitDlg(this);

		// ワーカースレッドの起動（サスペンド状態で生成）
		m_pWorkerThread = AfxBeginThread(
			ABDownloadWorkThreadProc,
			&waitDlg,
			THREAD_PRIORITY_NORMAL,
			0,
			CREATE_SUSPENDED);

		SAVEPATH = selDlg.GetPathName();
		if (find.FindFile(SAVEPATH)) {
			DeleteFile(SAVEPATH);
		}
		wchar_t Drive[MAX_PATH]{}, Dir[MAX_PATH]{}, Name[MAX_PATH]{}, Ext[MAX_PATH]{};
		_tsplitpath_s(SAVEPATH, Drive, Dir, Name, Ext);
		CString DRIVE = Drive, DIR = Dir, NAME = Name, EXT = Ext;

		m_hSavePath = SAVEPATH;
		m_hDLURI = SERVER + VER + _T("/production/") + UNITYVER + OS + INDEX;
		m_hDownloadMsg = _T("Downloading:'") + RES + _T("'...");

		// オートデリート設定（不要ならFALSEに）
		m_pWorkerThread->m_bAutoDelete = TRUE;
		m_pWorkerThread->ResumeThread();  // 実行開始

		// モーダル表示（内部で独自メッセージループが動く）
		waitDlg.DoModal();

		if (CMLTDABDDlg::SuspendFlag == 1) {
			CMLTDABDDlg::SuspendFlag = 0;
			MessageBox(_T("処理がキャンセルされました。"), _T("キャンセル"), MB_ICONWARNING | MB_OK);
			return;
		}
		if (CMLTDABDDlg::ExceptionFlag == 1) {
			CMLTDABDDlg::ExceptionFlag = 0;
			DWORD err = m_hLastError;
			CString str;
			str.Format(_T("エラーが発生しました。\n%u"), err);
			MessageBox((str), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}

		if (find.FindFile(SAVEPATH)) {
			if (223 >= GetFileSizeStat(SAVEPATH)) {
				DeleteFile(SAVEPATH);
				MessageBox(_T("ダウンロードに失敗しました。\nアクセスが拒否されました。"), _T("ダウンロードエラー"), MB_ICONERROR | MB_OK);
				return;
			}
			else if (223 < GetFileSizeStat(SAVEPATH)) {
				MessageBox(_T("保存が完了しました。"), _T("完了"), MB_ICONINFORMATION | MB_OK);
				ShellExecute(NULL, _T("open"), SAVEPATH.Left(SAVEPATH.ReverseFind('\\')), NULL, NULL, SW_SHOWNORMAL);
				return;
			}
			else {
				return;
			}
		}
		else {
			MessageBox(_T("ダウンロードに失敗しました。\nインターネット接続を確認してください。。"), _T("ダウンロードエラー"), MB_ICONERROR | MB_OK);
			return;
		}
	}
	else if (ret == IDCANCEL) {
		MessageBox(_T("キャンセルされました。"), _T("完了"), MB_ICONWARNING | MB_OK);
		return;
	}
	else {
		return;
	}
}
