
// OpenGLPick.h : OpenGLPick アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// COpenGLPickApp:
// このクラスの実装については、OpenGLPick.cpp を参照してください。
//

class COpenGLPickApp : public CWinApp
{
public:
	COpenGLPickApp();


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLPickApp theApp;
