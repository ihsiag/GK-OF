
// OpenGLBaseView.cpp : COpenGLBaseView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
//#include "OpenGLBase.h"
#endif

//#include "OpenGLBaseDoc.h"
#include "OpenGLBaseView.h"

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLBaseView

IMPLEMENT_DYNCREATE(COpenGLBaseView, CView)

BEGIN_MESSAGE_MAP(COpenGLBaseView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// COpenGLBaseView �R���X�g���N�V����/�f�X�g���N�V����

COpenGLBaseView::COpenGLBaseView() :
	m_hRC( NULL ),
	m_pDC( NULL ),
	m_cx( 0 ),
	m_cy( 0 )
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

COpenGLBaseView::~COpenGLBaseView()
{
}

BOOL COpenGLBaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// COpenGLBaseView �`��

void COpenGLBaseView::OnDraw(CDC* /*pDC*/)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
	if( !m_pDC )
	{
		return;
	}

	// �����_�����O�R���e�L�X�g�̐ݒ�
	// MDI�`��ɂ����ĕK�{�BSDI�ɂ����Ă͏ȗ���(InitializeOpenGL�֐����ŌĂяo���ς݂Ȃ̂Łj�B
	// �ȍ~��OpenGL�֐��ɂ��`��́A�w�肵�������_�����O�R���e�L�X��ɕ`�悳���B
	wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	PreRenderScene();

	glPushMatrix();
	RenderStockScene();
	glPopMatrix();

	glPushMatrix();
	RenderScene();
	glPopMatrix();

	PostRenderScene();

	glFinish();

	SwapBuffers( m_pDC->GetSafeHdc() );
}

// COpenGLBaseView �f�f

#ifdef _DEBUG
void COpenGLBaseView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLBaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDocument* COpenGLBaseView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocument)));
	return (CDocument*)m_pDocument;
}
#endif //_DEBUG

bool COpenGLBaseView::InitializeOpenGL()
{
	// �f�o�C�X�R���e�L�X�g�̍쐬
	m_pDC = new CClientDC( this );
	if( NULL == m_pDC )
	{
		ASSERT( !"m_pDC is NULL" );
		return false;
	}

	// OpenGL pixel format �̐ݒ�
	if( !SetupPixelFormat() )
	{
		ASSERT( !"SetupPixelFormat failed" );
		return false;
	}

	// �����_�����O�R���e�L�X�g�̍쐬
	m_hRC = wglCreateContext( m_pDC->GetSafeHdc() );
	if( 0 == m_hRC )
	{
		ASSERT( !"wglCreateContext failed" );
		return false;
	}

	// �����_�����O�R���e�L�X�g�̐ݒ�
	if( TRUE != wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
	{
		ASSERT( !"wglMakeCurrent failed" );
		return false;
	}

	// OpenGL�g���@�\���g����悤�ɂ���
	if( !InitOpenGLExtFuncs() )
	{
		ASSERT( !"InitOpenGLExtFuncs failed" );
		return false;
	}

	// �N���A����
	glClearColor( 0, 0, 0, 0 );	// �N���A�J���[
	glClearDepth( 1.0f );	// �N���A�[�x

	// �f�v�X����
	glEnable( GL_DEPTH_TEST );	// �f�v�X�e�X�g
	glDepthFunc( GL_LEQUAL );	//�f�v�X�t�@���N�i�������A��O�ɂ�����̂ŏ�`���Ă����j

	// �|���S������
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );	// �|���S���iGL_TRIANGLES���j�́A���ʋ��h��Ԃ��B
	glDisable( GL_CULL_FACE ); // ���������Ă���ʂ̃J�����O�i�J�����O���Ȃ������ʂ��`��j
	glEnable( GL_POLYGON_OFFSET_FILL ); // �|���S���I�t�Z�b�g�t�B���i�ʂƐ����d�Ȃ�ꍇ�̃J�X���h�~�j
	glPolygonOffset( 1.0f, 1.0f ); // �|���S���I�t�Z�b�g��

	// ���C�e�B���O����
	glDisable( GL_LIGHTING ); // ����
	glEnable( GL_NORMALIZE ); // OpenGL���Ŗ@���x�N�g����P�ʖ@���x�N�g��������悤�ɂ���
	glDisable( GL_COLOR_MATERIAL ); // �J���[�ݒ�l���}�e���A���Ƃ��Ďg�p

	return true;
}

bool COpenGLBaseView::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int iPixelFormat;
	if( 0 == ( iPixelFormat = ChoosePixelFormat( m_pDC->GetSafeHdc(), &pfd ) ) )
	{
		ASSERT( !"ChoosePixelFormat is failed" );
		return FALSE;
	}

	if( TRUE != SetPixelFormat( m_pDC->GetSafeHdc(), iPixelFormat, &pfd ) )
	{
		ASSERT( !"SetPixelFormat is failed" );
		return FALSE;
	}

	return true;
}

void COpenGLBaseView::UninitializeOpenGL()
{
	wglMakeCurrent( NULL, NULL );
	if( m_hRC )
	{
		wglDeleteContext( m_hRC );
		m_hRC = NULL;
	}
	if( m_pDC )
	{
		delete m_pDC;
		m_pDC = NULL;
	}
}

bool COpenGLBaseView::SetupViewport()
{
	glViewport( 0,
		0,
		m_cx,
		m_cy );
	return true;
}

bool COpenGLBaseView::SetupProjectionMatrix()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho( -m_cx * 0.5 / 10.0,
		m_cx * 0.5 / 10.0,
		-m_cy * 0.5 / 10.0,
		m_cy * 0.5 / 10.0,
		0.1,
		1000.0 );

	// ���e�ϊ��s��ɑ΂��鏈���͂����Ŋ����B
	// �ȍ~�̕ϊ��s�񏈗��́A���f���r���[�ϊ��s��ɑ΂��Ď��{�����悤�ɂ���B
	glMatrixMode( GL_MODELVIEW );
	return true;
}

bool COpenGLBaseView::SetupModelViewMatrix()
{
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt( 0.0, 0.0, 500.0,	// ���_
		0.0, 0.0, 0.0,	// �����_
		0.0, 1.0, 0.0 );	// ��x�N�g��

	return true;
}

void COpenGLBaseView::RenderStockScene()
{
	RenderAxis();
}

void COpenGLBaseView::RenderAxis()
{
	float	points[4][3];
	points[0][0] = 0.0;
	points[0][1] = 0.0;
	points[0][2] = 0.0;
	points[1][0] = 10;
	points[1][1] = 0.0;
	points[1][2] = 0.0;
	points[2][0] = 0.0;
	points[2][1] = 10;
	points[2][2] = 0.0;
	points[3][0] = 0.0;
	points[3][1] = 0.0;
	points[3][2] = 10;

	glPushAttrib( GL_CURRENT_BIT | GL_LINE_BIT );	// �F | �����

	glLineWidth( 2.0 );
	glBegin( GL_LINES );
	glColor3ub( 255, 0, 0 );
	glVertex3fv( points[0] );
	glVertex3fv( points[1] );
	glColor3ub( 0, 255, 0 );
	glVertex3fv( points[0] );
	glVertex3fv( points[2] );
	glColor3ub( 0, 0, 255 );
	glVertex3fv( points[0] );
	glVertex3fv( points[3] );
	glEnd();

	glPopAttrib();
}

// COpenGLBaseView ���b�Z�[�W �n���h���[


BOOL COpenGLBaseView::OnEraseBkgnd( CDC* pDC )
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	return TRUE;

	//return CView::OnEraseBkgnd( pDC );
}


void COpenGLBaseView::OnSize( UINT nType, int cx, int cy )
{
	CView::OnSize( nType, cx, cy );

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
	if( 0 >= cx || 0 >= cy )
	{
		return;
	}

	if( NULL == m_hRC )
	{
		// OpenGL����������
		InitializeOpenGL();
	}

	if( NULL != m_hRC )
	{
		// ��ʑ傫���̐ݒ�
		m_cx = cx;
		m_cy = cy;

		// �r���[�|�[�g�̐ݒ�
		SetupViewport();

		// ���e�ϊ��s��̐ݒ�
		SetupProjectionMatrix();

		// ���f�����O���r���[�C���O�ϊ��s��̐ݒ�
		SetupModelViewMatrix();
	}
}


void COpenGLBaseView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
	UninitializeOpenGL();
}
