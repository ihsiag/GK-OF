
// OpenGLTrackView.cpp : COpenGLTrackView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
//#include "OpenGLTrack.h"
#endif

//#include "OpenGLTrackDoc.h"
#include "OpenGLTrackView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLTrackView

IMPLEMENT_DYNCREATE(COpenGLTrackView, COpenGLBaseView)

BEGIN_MESSAGE_MAP(COpenGLTrackView, COpenGLBaseView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// COpenGLTrackView �R���X�g���N�V����/�f�X�g���N�V����

COpenGLTrackView::COpenGLTrackView() :
	m_eTrackingMode( TM_NONE ),
	m_fRenderingRate( 10 )
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B
	m_f3RenderingCenter[0] = 0.0;
	m_f3RenderingCenter[1] = 0.0;
	m_f3RenderingCenter[2] = 0.0;
	m_f16ViewingTransformMatrix[0] = 1.0f; m_f16ViewingTransformMatrix[1] = 0.0f; m_f16ViewingTransformMatrix[2] = 0.0f; m_f16ViewingTransformMatrix[3] = 0.0f;
	m_f16ViewingTransformMatrix[4] = 0.0f; m_f16ViewingTransformMatrix[5] = 1.0f; m_f16ViewingTransformMatrix[6] = 0.0f; m_f16ViewingTransformMatrix[7] = 0.0f;
	m_f16ViewingTransformMatrix[8] = 0.0f; m_f16ViewingTransformMatrix[9] = 0.0f; m_f16ViewingTransformMatrix[10] = 1.0f; m_f16ViewingTransformMatrix[11] = 0.0f;
	m_f16ViewingTransformMatrix[12] = 0.0f; m_f16ViewingTransformMatrix[13] = 0.0f; m_f16ViewingTransformMatrix[14] = 0.0f; m_f16ViewingTransformMatrix[15] = 1.0f;
}

COpenGLTrackView::~COpenGLTrackView()
{
}

BOOL COpenGLTrackView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return COpenGLBaseView::PreCreateWindow(cs);
}

// COpenGLTrackView �`��

//void COpenGLTrackView::OnDraw(CDC* /*pDC*/)
//{
//	CDocument* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
//}


// COpenGLTrackView �f�f

#ifdef _DEBUG
void COpenGLTrackView::AssertValid() const
{
	COpenGLBaseView::AssertValid();
}

void COpenGLTrackView::Dump(CDumpContext& dc) const
{
	COpenGLBaseView::Dump(dc);
}

CDocument* COpenGLTrackView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocument)));
	return (CDocument*)m_pDocument;
}
#endif //_DEBUG

void COpenGLTrackView::BeginTracking( CPoint point, ETRACKINGMODE eTrackingMode )
{
	SetCapture();
	m_eTrackingMode = eTrackingMode;
	m_ptLast = point;
}

void COpenGLTrackView::EndTracking()
{
	ReleaseCapture();
	m_eTrackingMode = TM_NONE;
}

void COpenGLTrackView::DoTracking( CPoint point )
{
	LONG lDeltaX = point.x - m_ptLast.x;
	LONG lDeltaY = point.y - m_ptLast.y;
	m_ptLast = point;
	switch( m_eTrackingMode )
	{
		case TM_NONE:
			break;
		case TM_ROTATION:
			{
				// �N���C�A���g�̈�̏c���̒Z�����̒������̃s�N�Z���������Ɣ����i180�x�j���悤��
				float fAngle_deg = (float)( sqrt( lDeltaX * lDeltaX + lDeltaY * lDeltaY ) * 180.0 / ( m_cx < m_cy ? m_cx : m_cy ) );
				// ��]�}�g���b�N�X�����݂̃I�u�W�F�N�g�t�H�[���}�g���b�N�X�Ɋ|�����킹��
				glPushMatrix();
				glLoadIdentity();
				glRotatef( fAngle_deg, (GLfloat)lDeltaY, (GLfloat)lDeltaX, 0 );
				glMultMatrixf( (GLfloat*)m_f16ViewingTransformMatrix );
				glGetFloatv( GL_MODELVIEW_MATRIX, (GLfloat*)m_f16ViewingTransformMatrix );
				glPopMatrix();
				// ���f�����O���r���[�C���O�ϊ��s��̐ݒ�
				SetupModelViewMatrix();
				Invalidate( FALSE );
			}
			break;
		case TM_PAN:
			{
				m_f3RenderingCenter[0] -= lDeltaX / m_fRenderingRate;
				m_f3RenderingCenter[1] += lDeltaY / m_fRenderingRate;
				// ���f�����O���r���[�C���O�ϊ��s��̐ݒ�
				SetupModelViewMatrix();
				Invalidate( FALSE );
			}
			break;
		case TM_ZOOM:
			{	// �g��E�k���ɂ��`��{������
				// +500�Ŕ{��2�{�ɁA+250�Ŕ{��1.5�{�ɁA
				// -500�Ŕ{��0.5�{�ɁA-1000�Ŕ{��0.25�{��
				m_fRenderingRate *= (float)pow( 2, -lDeltaY * 0.002f );
				// ���e�ϊ��s��̐ݒ�
				SetupProjectionMatrix();
				Invalidate( FALSE );
			}
			break;
		default:
			ASSERT( !"���Ή�" );
			break;
	}
}

bool COpenGLTrackView::SetupProjectionMatrix()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho( -m_cx * 0.5 / m_fRenderingRate,	// left
		m_cx * 0.5 / m_fRenderingRate,	// right
		-m_cy * 0.5 / m_fRenderingRate,	// buttom
		m_cy * 0.5 / m_fRenderingRate,	// top
		0.1,			// near
		1000.0 );			// far

	// ���e�ϊ��s��ɑ΂��鏈���͂����Ŋ����B
	// �ȍ~�̕ϊ��s�񏈗��́A���f���r���[�ϊ��s��ɑ΂��Ď��{�����悤�ɂ���B
	glMatrixMode( GL_MODELVIEW );
	return true;
}

bool COpenGLTrackView::SetupModelViewMatrix()
{
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt( m_f3RenderingCenter[0], m_f3RenderingCenter[1], m_f3RenderingCenter[2] + 500.0,	// ���_
		m_f3RenderingCenter[0], m_f3RenderingCenter[1], m_f3RenderingCenter[2],			// �����_
		0.0, 1.0, 0.0 );	// ��x�N�g��

	glMultMatrixf( (GLfloat*)m_f16ViewingTransformMatrix );	// �\����]�i�����f����]�j

	return true;
}

// COpenGLTrackView ���b�Z�[�W �n���h���[


void COpenGLTrackView::OnLButtonDown( UINT nFlags, CPoint point )
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	BeginTracking( point, TM_ROTATION );

	COpenGLBaseView::OnLButtonDown( nFlags, point );
}

void COpenGLTrackView::OnLButtonUp( UINT nFlags, CPoint point )
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	EndTracking();

	COpenGLBaseView::OnLButtonUp( nFlags, point );
}

void COpenGLTrackView::OnMButtonDown( UINT nFlags, CPoint point )
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	BeginTracking( point, TM_PAN );

	COpenGLBaseView::OnMButtonDown( nFlags, point );
}

void COpenGLTrackView::OnMButtonUp( UINT nFlags, CPoint point )
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	EndTracking();

	COpenGLBaseView::OnMButtonUp( nFlags, point );
}

void COpenGLTrackView::OnMouseMove( UINT nFlags, CPoint point )
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	DoTracking( point );

	COpenGLBaseView::OnMouseMove( nFlags, point );
}

BOOL COpenGLTrackView::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	BeginTracking( pt, TM_ZOOM );
	CPoint	pt_delta( pt.x - zDelta / 3, pt.y - zDelta / 3 );
	DoTracking( pt_delta );
	EndTracking();

	return COpenGLBaseView::OnMouseWheel( nFlags, zDelta, pt );
}

