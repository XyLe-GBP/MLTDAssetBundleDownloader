#pragma once

const int ID_UPDATE_STATUS = 40000;

#define WM_PROCESS_FINISHED  (WM_USER + 1)
#define WM_APPEND_TEXT  (WM_USER + 2)
// PROGRESSDLG ダイアログ

class PROGRESSDLG : public CDialogEx
{
	DECLARE_DYNAMIC(PROGRESSDLG)

public:
	PROGRESSDLG(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~PROGRESSDLG();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRESSDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnProcessFinished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAppendText(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
private:
	CString  m_strAccum;
	// ダイアログ上の静的テキストコントロール
	CStatic m_OutputStatic;

	// プログレスバー
	CProgressCtrl m_Progress;

	// タイマー ID はひとつだけ
	UINT_PTR m_nTimerID{ 0 };

	HDC hDCBackBuffer;
	HDC hDCStatic;
	HBRUSH m_Hbrush;
	CRect rc;

	CWinThread* pMainThread{};
	CProgressCtrl xv_Progress;
	CStatic m_Static;
	CString m_Logbuffer;

	CString MAX;
	CString POS;
	CString PROGRESSTEXT;
	//UINT_PTR m_TimerID;
	//UINT_PTR m_hTimerID;
	UINT MAX_POS;
	UINT CUR_POS;
	UINT ExceptionCounter = 0;
	UINT ValueFlag = 0;
	void UpdateProgressText();
public:
	afx_msg void OnBnClickedButtonCancel();
	static CString m_ErrorMsg;
};
