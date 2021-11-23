
// OpenGLBaseView.h : COpenGLBaseView �N���X�̃C���^�[�t�F�C�X
//

#pragma once

#include <gl\gl.h>
#include <gl\glu.h>
#include "OpenGLExtFuncs.h"

class COpenGLBaseView : public CView
{
	// �����o�ϐ�
private:
	HGLRC	m_hRC;
	CDC*	m_pDC;
protected:
	int		m_cx;
	int		m_cy;

	// �����o�֐�
private:
	bool	InitializeOpenGL();
	bool	SetupPixelFormat();
	bool	SetupViewport();
	bool	PreRenderScene() { return true; }
	void	RenderStockScene();
	bool	PostRenderScene() { return true; }
	void	RenderAxis();
protected:
	virtual void	UninitializeOpenGL();
	virtual bool	SetupProjectionMatrix();
	virtual bool	SetupModelViewMatrix();
	virtual bool	RenderScene() { return true; }

protected: // �V���A��������̂ݍ쐬���܂��B
	COpenGLBaseView();
	DECLARE_DYNCREATE(COpenGLBaseView)

// ����
public:
	CDocument* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����
public:
	virtual ~COpenGLBaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // OpenGLBaseView.cpp �̃f�o�b�O �o�[�W����
inline CDocument* COpenGLBaseView::GetDocument() const
   { return reinterpret_cast<CDocument*>(m_pDocument); }
#endif

