// PROGRESSDLG.cpp : 実装ファイル
//

#include "pch.h"
#include "MLTDABD.h"
#include "PROGRESSDLG.h"
#include "afxdialogex.h"


// PROGRESSDLG ダイアログ

IMPLEMENT_DYNAMIC(PROGRESSDLG, CDialogEx)

PROGRESSDLG::PROGRESSDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROGRESSDIALOG, pParent)
{

}

PROGRESSDLG::~PROGRESSDLG()
{
}

void PROGRESSDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PROGRESSDLG, CDialogEx)
END_MESSAGE_MAP()


// PROGRESSDLG メッセージ ハンドラー
