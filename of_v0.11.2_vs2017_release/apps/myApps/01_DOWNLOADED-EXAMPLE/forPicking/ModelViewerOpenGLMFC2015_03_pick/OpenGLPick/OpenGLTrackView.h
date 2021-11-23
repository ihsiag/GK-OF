
// OpenGLTrackView.h : COpenGLTrackView �N���X�̃C���^�[�t�F�C�X
//

#pragma once

#include "OpenGLBaseView.h"

// TrackingMode
enum ETRACKINGMODE
{
	TM_NONE = 0,
	TM_ROTATION,
	TM_PAN,
	TM_ZOOM,
};

class COpenGLTrackView : public COpenGLBaseView
{
	// �����o�ϐ�
private:
	ETRACKINGMODE	m_eTrackingMode;
	CPoint			m_ptLast;
	GLfloat			m_f3RenderingCenter[3];		// �`�撆�S
	GLfloat			m_fRenderingRate;			// �g�嗦
	GLfloat			m_f16ViewingTransformMatrix[16];

	// �����o�֐�
private:
	void	BeginTracking( CPoint point, ETRACKINGMODE eTrackingMode );
	void	EndTracking();
	void	DoTracking( CPoint point );
	bool	SetupProjectionMatrix();
	bool	SetupModelViewMatrix();

protected: // �V���A��������̂ݍ쐬���܂��B
	COpenGLTrackView();
	DECLARE_DYNCREATE(COpenGLTrackView)

// ����
public:
	CDocument* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
//	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����
public:
	virtual ~COpenGLTrackView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnMButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
};

#ifndef _DEBUG  // OpenGLTrackView.cpp �̃f�o�b�O �o�[�W����
inline CDocument* COpenGLTrackView::GetDocument() const
   { return reinterpret_cast<CDocument*>(m_pDocument); }
#endif

