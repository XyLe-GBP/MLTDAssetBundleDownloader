#pragma once


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

	DECLARE_MESSAGE_MAP()
};
