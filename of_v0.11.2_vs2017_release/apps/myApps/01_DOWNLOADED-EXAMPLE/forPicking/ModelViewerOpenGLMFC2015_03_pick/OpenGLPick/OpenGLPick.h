
// OpenGLPick.h : OpenGLPick �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// COpenGLPickApp:
// ���̃N���X�̎����ɂ��ẮAOpenGLPick.cpp ���Q�Ƃ��Ă��������B
//

class COpenGLPickApp : public CWinApp
{
public:
	COpenGLPickApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLPickApp theApp;
