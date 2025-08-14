
// MLTDABD.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMLTDABDApp:
// このクラスの実装については、MLTDABD.cpp を参照してください
//

class CMLTDABDApp : public CWinApp
{
public:
	CMLTDABDApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	BOOL ThreadFlag = false;

	DECLARE_MESSAGE_MAP()
};

extern CMLTDABDApp theApp;
