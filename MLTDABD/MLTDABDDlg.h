
// MLTDABDDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include <memory>
#include <string>

// CMLTDABDDlg ダイアログ
class CMLTDABDDlg : public CDialogEx
{
// コンストラクション
	DECLARE_DYNAMIC(CMLTDABDDlg)
	friend class PROGRESSDLG;
public:
	CMLTDABDDlg(CWnd* pParent = nullptr);	// 標準コンストラクター
	virtual ~CMLTDABDDlg();
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
	// ワーカーからの命令を受けてメインスレッドが実行する関数。
	afx_msg void OnAboutMLTDABD();
	afx_msg void OnUpdateCheck();
	afx_msg void OnBnClickedRadioPrtAndroid();
	afx_msg void OnBnClickedRadioPrtIos();
	afx_msg void OnCbnSelchangeComboVersion();
	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnBnClickedButtonBundleinfoUpdate();
	afx_msg void OnBnClickedRadioSrvOriginal();
	afx_msg void OnBnClickedRadioSrvMirror();
	CComboBox m_hCmbAssetVer;
	CStatic m_hStatic_Hash;
	CStatic m_hStatic_Date;
	//afx_msg void OnBnClickedButtonUabmRead();
	static HANDLE m_hCancelEvent;
	static CWinThread* m_pWorkerThread;
	static CComboBox m_hCmbUabRes;
	afx_msg void OnCbnSelchangeComboUabres();
	afx_msg void OnBnClickedButtonUabdownload();
	static CString m_hRet;
	static CString m_hSavePath, m_hDLURI, m_hShapedFilePath;
	static CString m_hDownloadMsg;
	static TCHAR* m_hSavepathT;
	static DWORD m_hLastError;
	// PROGRESSDLGで中止ボタンを押した際のフラグ
	static UINT SuspendFlag;
	// PROGRESSDLGでエラーが発生した際のフラグ
	static UINT ExceptionFlag;
	// 現在どのスレッドを実行しているかのフラグ
	static UINT ProgressThreadFlag;
	static UINT PROGRESS_COUNT;
	
};
