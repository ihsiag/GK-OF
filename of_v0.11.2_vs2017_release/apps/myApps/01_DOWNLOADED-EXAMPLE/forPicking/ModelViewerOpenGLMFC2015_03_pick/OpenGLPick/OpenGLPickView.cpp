
// OpenGLPickView.cpp : COpenGLPickView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "OpenGLPick.h"
#endif

#include "OpenGLPickDoc.h"
#include "OpenGLPickView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLPickView

IMPLEMENT_DYNCREATE(COpenGLPickView, COpenGLTrackView)

BEGIN_MESSAGE_MAP(COpenGLPickView, COpenGLTrackView)
	ON_WM_SIZE()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// COpenGLPickView �R���X�g���N�V����/�f�X�g���N�V����

COpenGLPickView::COpenGLPickView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B
	memset( m_auiName_picked, 0x00, NAMEARRAYSIZE * sizeof( unsigned int ) );

	m_uiTextureID = 0;
	m_uiRenderBufferID = 0;
	m_uiFrameBufferID = 0;
}

COpenGLPickView::~COpenGLPickView()
{
}

BOOL COpenGLPickView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return COpenGLTrackView::PreCreateWindow(cs);
}

// COpenGLPickView �`��

//void COpenGLPickView::OnDraw(CDC* /*pDC*/)
//{
//	COpenGLPickDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
//}


// COpenGLPickView �f�f

#ifdef _DEBUG
void COpenGLPickView::AssertValid() const
{
	COpenGLTrackView::AssertValid();
}

void COpenGLPickView::Dump(CDumpContext& dc) const
{
	COpenGLTrackView::Dump(dc);
}

COpenGLPickDoc* COpenGLPickView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLPickDoc)));
	return (COpenGLPickDoc*)m_pDocument;
}
#endif //_DEBUG

void COpenGLPickView::CreateFrameBuffer( int iWidth, int iHeight )
{
	// ���O�̐���
	if( 0 == m_uiTextureID )
	{
		glGenTextures( 1, &m_uiTextureID );
		glGenRenderbuffers( 1, &m_uiRenderBufferID );
		glGenFramebuffers( 1, &m_uiFrameBufferID );
	}

	// �e�N�X�`���̍\�z
	glBindTexture( GL_TEXTURE_2D, m_uiTextureID );	// �e�N�X�`���̃o�C���h
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_cx, m_cy, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );	// �����Ƃ��߂��Z���̐F���g�p���F��Ԃ��Ȃ��BGL_LINEAR�́A�F��Ԃ���B
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );	// �����Ƃ��߂��Z���̐F���g�p���F��Ԃ��Ȃ��BGL_LINEAR�́A�F��Ԃ���B
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP ); // �摜�̒[�̃s�N�Z���̐F���g��
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP ); // �摜�̒[�̃s�N�Z���̐F���g��
	glBindTexture( GL_TEXTURE_2D, 0 );	// �o�C���h�̉���

	// �����_�[�o�b�t�@�[�̍\�z
	glBindRenderbuffer( GL_RENDERBUFFER, m_uiRenderBufferID );		// �����_�[�o�b�t�@�̃o�C���h
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_cx, m_cy );		// �����_�[�o�b�t�@�̐[�x�A�T�C�Y�̐ݒ�
	glBindRenderbuffer( GL_RENDERBUFFER, 0 ); // �o�C���h�̉���
}

void COpenGLPickView::DestroyFrameBuffer()
{
	if( 0 == m_uiTextureID )
	{
		return;
	}

	glDeleteFramebuffers( 1, &m_uiFrameBufferID );
	glDeleteRenderbuffers( 1, &m_uiRenderBufferID );
	glDeleteTextures( 1, &m_uiTextureID );

	m_uiFrameBufferID = 0;
	m_uiRenderBufferID = 0;
	m_uiTextureID = 0;
}

void COpenGLPickView::UninitializeOpenGL()
{
	DestroyFrameBuffer();

	COpenGLTrackView::UninitializeOpenGL();
}

bool COpenGLPickView::RenderScene()
{
	RenderModel( RM_RENDER );

	return true;
}

void COpenGLPickView::RenderModel( ERENDERMODE eRenderMode )
{
	unsigned int uiCountPoint = 8;
	float points[8][3] = { -5, -5, -5,
							  5, -5, -5,
							  5,  5, -5,
							 -5,  5, -5,
							 -5, -5,  5,
							  5, -5,  5,
							  5,  5,  5,
							 -5,  5,  5 };
	unsigned int uiCountTriangle = 12;
	unsigned int triangles[12][3] = { 0, 1, 3,
							  1, 2, 3,
							  1, 5, 2,
							  5, 6, 2,
							  5, 4, 6,
							  4, 7, 6,
							  4, 0, 7,
							  0, 3, 7,
							  3, 2, 7,
							  2, 6, 7,
							  4, 5, 0,
							  5, 1, 0 };
	unsigned int uiIndexTriangle;
	unsigned int uiIndexLine;
	unsigned int uiIndexPoint;
	unsigned int ui3;

	glPushAttrib( GL_ALL_ATTRIB_BITS );	// �A�g���r���[�g���A�ł���悤�ɁA��ǉ�

	// ��
	if( RM_RENDER == eRenderMode )
	{
		glColor3f( 0.5f, 0.5f, 0.0f );
	}
	if( RM_PICK_ELEMENTTYPE == eRenderMode )
	{
		glColor3f( 1.0f, 0.0f, 0.0f );
	}
	for( uiIndexTriangle = 0; uiIndexTriangle < uiCountTriangle; uiIndexTriangle++ )
	{
		if( RM_PICK_ELEMENTID == eRenderMode )
		{
			glColor3ub( GetRValue(uiIndexTriangle), GetGValue(uiIndexTriangle), GetBValue(uiIndexTriangle) );
		}
		glBegin( GL_TRIANGLES );
		glVertex3fv( points[triangles[uiIndexTriangle][0]] );
		glVertex3fv( points[triangles[uiIndexTriangle][1]] );
		glVertex3fv( points[triangles[uiIndexTriangle][2]] );
		glEnd();
	}
	// �s�b�N�ʂ̕`��
	if( RM_RENDER == eRenderMode )
	{
		if( RET_FACE == m_auiName_picked[1] )
		{
			uiIndexTriangle = m_auiName_picked[2];
			glColor3f( 1.0f, 1.0f, 0.0f );	// �s�b�N�F
			glBegin( GL_TRIANGLES );
			glVertex3fv( points[triangles[uiIndexTriangle][0]] );
			glVertex3fv( points[triangles[uiIndexTriangle][1]] );
			glVertex3fv( points[triangles[uiIndexTriangle][2]] );
			glEnd();
		}
	}
	// ��
	glLineWidth( 2.0 );
	if( RM_RENDER == eRenderMode )
	{
		glColor3f( 0.0f, 0.5f, 0.5f );
	}
	if( RM_PICK_ELEMENTTYPE == eRenderMode )
	{
		glColor3f( 0.0f, 1.0f, 0.0f );
	}
	for( uiIndexTriangle = 0; uiIndexTriangle < uiCountTriangle; ++uiIndexTriangle )
	{
		for( ui3 = 0; ui3 < 3; ++ui3 )
		{
			if( RM_PICK_ELEMENTID == eRenderMode )
			{
				uiIndexLine = uiIndexTriangle * 3 + ui3;
				glColor3ub( GetRValue(uiIndexLine), GetGValue(uiIndexLine), GetBValue(uiIndexLine) );
			}
			glBegin( GL_LINES );
			glVertex3fv( points[triangles[uiIndexTriangle][( ui3 + 0 ) % 3]] );
			glVertex3fv( points[triangles[uiIndexTriangle][( ui3 + 1 ) % 3]] );
			glEnd();
		}
	}
	// �s�b�N���̕`��
	if( RM_RENDER == eRenderMode )
	{
		if( RET_LINE == m_auiName_picked[1] )
		{
			uiIndexLine = m_auiName_picked[2];
			uiIndexTriangle = uiIndexLine / 3;
			ui3 = uiIndexLine % 3;
			glLineWidth( 5.0f );
			glColor3f( 0.0f, 1.0f, 1.0f );
			glBegin( GL_LINES );
			glVertex3fv( points[triangles[uiIndexTriangle][( ui3 + 0 ) % 3]] );
			glVertex3fv( points[triangles[uiIndexTriangle][( ui3 + 1 ) % 3]] );
			glEnd();
		}
	}
	// �_
	glPointSize( 5.0 );
	if( RM_RENDER == eRenderMode )
	{
		glColor3f( 0.5f, 0.0f, 0.5f );
	}
	if( RM_PICK_ELEMENTTYPE == eRenderMode )
	{
		glColor3f( 0.0f, 0.0f, 1.0f );
	}
	for( uiIndexPoint = 0; uiIndexPoint < uiCountPoint; uiIndexPoint++ )
	{
		if( RM_PICK_ELEMENTID == eRenderMode )
		{
			glColor3ub( GetRValue(uiIndexPoint), GetGValue(uiIndexPoint), GetBValue(uiIndexPoint) );
		}
		glBegin( GL_POINTS );
		glVertex3fv( points[uiIndexPoint] );
		glEnd();
	}
	// �s�b�N�_�̕`��
	if( RM_RENDER == eRenderMode )
	{
		if( RET_POINT == m_auiName_picked[1] )
		{
			glPointSize( 10.0f );
			glColor3f( 1.0f, 0.0f, 1.0f );
			uiIndexPoint = m_auiName_picked[2];
			glBegin( GL_POINTS );
			glVertex3fv( points[uiIndexPoint] );
			glEnd();
		}
	}

	glPopAttrib();	// �A�g���r���[�g�̕��A
	return;
}

// �s�b�L���O
int COpenGLPickView::DoPicking( int x, int y )
{
	// �t���[���o�b�t�@�̃o�C���h
	glBindFramebuffer( GL_FRAMEBUFFER, m_uiFrameBufferID );
	// �J���[�A�^�b�`�����g�Ƃ��ăe�N�X�`�����w�肷��
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uiTextureID, 0 );
	// �[�x�A�^�b�`�����g�Ƃ��ă����_�[�o�b�t�@���w�肷��
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uiRenderBufferID );

	int iCountHit = 0;
	int iStatus = glCheckFramebufferStatus( GL_FRAMEBUFFER );
	if( GL_FRAMEBUFFER_COMPLETE != iStatus )
	{	// �t���[���o�b�t�@�[�����S�łȂ�
		// �E�B���h�E�V�X�e�����񋟂���t���[���o�b�t�@�ɍ����ւ�
		glBindFramebuffer( GL_FRAMEBUFFER, 0 );
		return false;
	}

	GLubyte r;
	GLubyte g;
	GLubyte b;

	// ���O��̔z��
	unsigned int aauiNamePickRegionPixel[PICKREGIONPIXELCOUNT][NAMEARRAYSIZE];
	// ���O��̔z��̏�����
	memset( aauiNamePickRegionPixel, 0x00, PICKREGIONPIXELCOUNT * NAMEARRAYSIZE * sizeof( unsigned int ) );
	// �s�N�Z���F�̔z��
	GLubyte abtColorPickRegionPixel[PICKREGIONPIXELCOUNT * 4];
	// �s�N�Z���F�̔z��̏�����
	memset( abtColorPickRegionPixel, 0x00, PICKREGIONPIXELCOUNT * 4 * sizeof( GLubyte ) );

	glDisable( GL_LIGHTING ); // ��
	glDisable( GL_BLEND ); // ����������уA���`�G�C���A�V���O

	// �s�b�N�`��i�v�f�^�C�v�ʁj
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	RenderModel( RM_PICK_ELEMENTTYPE );
	glReadPixels( x - PICKREGIONOFFSET,
		m_cy - y - PICKREGIONOFFSET,
		1 + 2 * PICKREGIONOFFSET,
		1 + 2 * PICKREGIONOFFSET,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		abtColorPickRegionPixel );
	// �s�b�N�̈�̐F���s�b�N���z��ɕϊ�
	for( unsigned int ui = 0; ui < PICKREGIONPIXELCOUNT; ++ui )
	{
		r = abtColorPickRegionPixel[ui * 4 + 0];
		g = abtColorPickRegionPixel[ui * 4 + 1];
		b = abtColorPickRegionPixel[ui * 4 + 2];
		if( 255 == r )
		{ // ��
			aauiNamePickRegionPixel[ui][1] = RET_FACE;
			++iCountHit;
		}
		else if( 255 == g )
		{ // ��
			aauiNamePickRegionPixel[ui][1] = RET_LINE;
			++iCountHit;
		}
		else if( 255 == b )
		{ // �_
			aauiNamePickRegionPixel[ui][1] = RET_POINT;
			++iCountHit;
		}
	}
	if( 0 != iCountHit )
	{ // �q�b�g����
		// �s�b�N�`��i�v�f�ԍ��ʁj
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		RenderModel( RM_PICK_ELEMENTID );
		glReadPixels( x - PICKREGIONOFFSET,
			m_cy - y - PICKREGIONOFFSET,
			1 + 2 * PICKREGIONOFFSET,
			1 + 2 * PICKREGIONOFFSET,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			abtColorPickRegionPixel );
		// �s�b�N�̈�̐F���s�b�N���z��ɕϊ�
		for( unsigned int ui = 0; ui < PICKREGIONPIXELCOUNT; ui++ )
		{
			r = abtColorPickRegionPixel[ui * 4 + 0];
			g = abtColorPickRegionPixel[ui * 4 + 1];
			b = abtColorPickRegionPixel[ui * 4 + 2];
			// �F��ԍ��ɕϊ����A���O�z��ɃZ�b�g
			aauiNamePickRegionPixel[ui][2] = RGB( r, g, b );
		}

		// �s�b�N�̈�s�N�Z�����Ӓ肵�A�s�b�N�v�f����肷��
		IdentifyPickRegionPixels( PICKREGIONPIXELCOUNT, aauiNamePickRegionPixel );
	}

	// �E�B���h�E�V�X�e�����񋟂���t���[���o�b�t�@�ɍ����ւ�
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

	return ( 0 != iCountHit );
}

// �s�b�N�̈�s�N�Z�����Ӓ肵�A�s�b�N�v�f����肷��
void COpenGLPickView::IdentifyPickRegionPixels( unsigned int uiCountPickRegionPixel, unsigned int aauiNamePickRegionPixel[][NAMEARRAYSIZE] )
{
	int  iId_selected = -1;
	unsigned int  uiElementType_selected = RET_FACE + 1;
	long lSquareDist_selected = ( 2 + PICKREGIONOFFSET ) * ( 2 + PICKREGIONOFFSET ) + ( 2 + PICKREGIONOFFSET ) * ( 2 + PICKREGIONOFFSET );
	long lSquareDist_current;
	int  x;
	int  y;
	for( unsigned int ui = 0; ui < uiCountPickRegionPixel; ui++ )
	{
		if( 0 == aauiNamePickRegionPixel[ui][1] )
		{ // ���f���̊O��
			continue;
		}
		if( uiElementType_selected < aauiNamePickRegionPixel[ui][1] )
		{ // �v�f�^�C�v�I�ɁA�D�揇�ʂ��Ⴂ
			continue;
		}
		if( uiElementType_selected > aauiNamePickRegionPixel[ui][1] )
		{ // �v�f�^�C�v�I�ɁA�D�揇�ʂ��Ⴂ
			iId_selected = ui;
			uiElementType_selected = aauiNamePickRegionPixel[ui][1];
			x = ui % ( 1 + 2 * PICKREGIONOFFSET ) - PICKREGIONOFFSET;
			y = ui / ( 1 + 2 * PICKREGIONOFFSET ) - PICKREGIONOFFSET;
			lSquareDist_selected = x * x + y * y;
			continue;
		}
		// �v�f�^�C�v�I�ɁA�D�揇�ʂ������ꍇ�́A�s�b�N�̈�̒��S�ɋ߂����̂��D��x�������B
		x = ui % ( 1 + 2 * PICKREGIONOFFSET ) - PICKREGIONOFFSET;
		y = ui / ( 1 + 2 * PICKREGIONOFFSET ) - PICKREGIONOFFSET;
		lSquareDist_current = x * x + y * y;
		if( lSquareDist_selected > lSquareDist_current )
		{
			iId_selected = ui;
			uiElementType_selected = aauiNamePickRegionPixel[ui][1];
			lSquareDist_selected = lSquareDist_current;
			continue;
		}
	}

	if( -1 == iId_selected )
	{
		return;
	}

	// ���O�񃁃��o�̍X�V
	memcpy( m_auiName_picked, aauiNamePickRegionPixel[iId_selected], NAMEARRAYSIZE * sizeof( unsigned int ) );
}

// COpenGLPickView ���b�Z�[�W �n���h���[


void COpenGLPickView::OnSize( UINT nType, int cx, int cy )
{
	COpenGLTrackView::OnSize( nType, cx, cy );

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
	if( 0 >= cx || 0 >= cy )
	{
		return;
	}

	CreateFrameBuffer( cx, cy );
}


void COpenGLPickView::OnRButtonUp( UINT nFlags, CPoint point )
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	if( 0 < DoPicking( point.x, point.y ) )
	{	// �s�b�N�ɐ���������ĕ`��
		Invalidate( FALSE );
		return;
	}

	COpenGLTrackView::OnRButtonUp( nFlags, point );
}
