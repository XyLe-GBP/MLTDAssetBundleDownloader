
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



CMLTDABDDlg::CMLTDABDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MLTDABD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_ML);
}

void CMLTDABDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VERSION, m_hCmbAssetVer);
	DDX_Control(pDX, IDC_STATIC_HASH, m_hStatic_Hash);
	DDX_Control(pDX, IDC_STATIC_UPDATE_DATE, m_hStatic_Date);
	DDX_Control(pDX, IDC_COMBO_UABRES, m_hCmbUabRes);
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
		SAVEPATH = selDlg.GetPathName();
		if (find.FindFile(SAVEPATH)) {
			DeleteFile(SAVEPATH);
		}
		wchar_t Drive[MAX_PATH]{}, Dir[MAX_PATH]{}, Name[MAX_PATH]{}, Ext[MAX_PATH]{};
		_tsplitpath_s(SAVEPATH, Drive, Dir, Name, Ext);
		CString DRIVE = Drive, DIR = Dir, NAME = Name, EXT = Ext;
		DownloadFile(SERVER + VER + _T("/production/") + UNITYVER + OS + INDEX, SAVEPATH, 1024);
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
							_tcscpy_s(&savePathT[0], 512, _T("uabmr ") + SAVEPATH + _T(" -d ") + DRIVE + DIR + NAME + _T("_spd.data"));
							FP = DRIVE + DIR + NAME + _T("_spd.data");
						}
						else if (EXT == ".unity3d" || EXT == ".UNITY3D") {
							_tcscpy_s(&savePathT[0], 512, _T("uabmr ") + SAVEPATH + _T(" -d ") + DRIVE + DIR + NAME + _T("_spd.unity3d"));
							FP = DRIVE + DIR + NAME + _T("_spd.unity3d");
						}
						else if (EXT == ".txt" || EXT == ".TXT") {
							_tcscpy_s(&savePathT[0], 512, _T("uabmr ") + SAVEPATH + _T(" -d ") + DRIVE + DIR + NAME + _T("_spd.txt"));
							FP = DRIVE + DIR + NAME + _T("_spd.txt");
						}
						else {
							return; // Error
						}
					}

					PROGRESSDLG* Dlg = new PROGRESSDLG;
					MSG msg;
					Dlg->Create(IDD_PROGRESSDIALOG);
					Dlg->ShowWindow(SW_SHOW);
					while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
						if (!AfxGetApp()->PumpMessage())
						{
							::PostQuitMessage(0);
							break;
						}
					}

					STARTUPINFO si;
					memset(&si, 0, sizeof(STARTUPINFO));
					PROCESS_INFORMATION pi;
					memset(&pi, 0, sizeof(PROCESS_INFORMATION));
					si.dwFlags = STARTF_USESHOWWINDOW;
					si.wShowWindow = SW_HIDE;
					::CreateProcess(NULL, savePathT, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

					CloseHandle(pi.hThread);
					WaitForSingleObject(pi.hProcess, INFINITE);
					CloseHandle(pi.hProcess);

					Dlg->DestroyWindow();
					SAFE_DELETE(Dlg);
					SAFE_FREE(savePathT);

					DeleteFile(SAVEPATH);

					if (find.FindFile(FP)) {
						MessageBox(_T("整形が完了しました。\nUABをダウンロードする場合は、下のコンボボックスから選択して\nダウンロードを行ってください。"), _T("完了"), MB_ICONINFORMATION | MB_OK);
						//ShellExecute(NULL, _T("open"), FP.Left(FP.ReverseFind('\\')), NULL, NULL, SW_SHOWNORMAL);

						PROGRESSDLG* Dlg = new PROGRESSDLG;

						std::ifstream fin(FP);
						if (!fin) {
							MessageBox(_T("予期せぬエラーが発生しました。\n(ファイルを開くことが出来ません。)"), _T("エラー"), MB_ICONERROR | MB_OK);
							return;
						}

						std::ofstream fout(".\\uabm.abddata");
						if (!fout) {
							MessageBox(_T("予期せぬエラーが発生しました。\n(ファイルを書き込むことが出来ません。)"), _T("エラー"), MB_ICONERROR | MB_OK);
							return;
						}

						MSG msg;
						Dlg->Create(IDD_PROGRESSDIALOG);
						Dlg->ShowWindow(SW_SHOW);
						while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
							if (!AfxGetApp()->PumpMessage())
							{
								::PostQuitMessage(0);
								break;
							}
						}

						std::string ss;

						while (std::getline(fin, ss, '\n')) {
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
								fout << buf << ",";
								BUF = buf.c_str();
								m_hCmbUabRes.AddString(BUF);
								break;
							}

							for (const auto& pos : findVec2) {
								size_t ps = pos + 10, ds = ss.find(",") - 10;
								CString BUF;
								buf = ss.substr(ps, ds);
								fout << buf << "\n";
								BUF = buf.c_str();
								break;
							}
						}

						Dlg->DestroyWindow();
						SAFE_DELETE(Dlg);

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
		DownloadFile(_T("\x68\x74\x74\x70\x73\x3a\x2f\x2f\x61\x70\x69\x2e\x6d\x61\x74\x73\x75\x72\x69\x68\x69\x2e\x6d\x65\x2f\x6d\x6c\x74\x64\x2f\x76\x31\x2f\x76\x65\x72\x73\x69\x6f\x6e\x2f\x61\x73\x73\x65\x74\x73"), _T(".\\vsd.abddata"), 1024);
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
			MessageBox(_T("更新に失敗しました。\nインターネット接続を確認してください。"), _T("UAB更新エラー"), MB_ICONERROR | MB_OK);
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
		SAVEPATH = selDlg.GetPathName();
		if (find.FindFile(SAVEPATH)) {
			DeleteFile(SAVEPATH);
		}
		wchar_t Drive[MAX_PATH]{}, Dir[MAX_PATH]{}, Name[MAX_PATH]{}, Ext[MAX_PATH]{};
		_tsplitpath_s(SAVEPATH, Drive, Dir, Name, Ext);
		CString DRIVE = Drive, DIR = Dir, NAME = Name, EXT = Ext;
		DownloadFile(SERVER + VER + _T("/production/") + UNITYVER + OS + INDEX, SAVEPATH, 1024);
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
