
// MLTDABDDlg.h : ヘッダー ファイル
//

#pragma once


// CMLTDABDDlg ダイアログ
class CMLTDABDDlg : public CDialogEx
{
// コンストラクション
public:
	CMLTDABDDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MLTDABD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAboutMLTDABD();
	afx_msg void OnUpdateCheck();
	afx_msg void OnBnClickedRadioPrtAndroid();
	afx_msg void OnBnClickedRadioPrtIos();
	afx_msg void OnCbnSelchangeComboVersion();
	afx_msg void OnBnClickedButtonDownload();
	CComboBox m_hCmbAssetVer;
	CStatic m_hStatic_Hash;
	CStatic m_hStatic_Date;
	afx_msg void OnBnClickedButtonBundleinfoUpdate();
	afx_msg void OnBnClickedRadioSrvOriginal();
	afx_msg void OnBnClickedRadioSrvMirror();
};
