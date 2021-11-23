
// OpenGLPickView.h : COpenGLPickView クラスのインターフェイス
//

#pragma once

#include "OpenGLTrackView.h"

#define	NAMEARRAYSIZE			(10)	// 名前列の大きさ
#define PICKREGIONOFFSET		(5)		// ピック領域のオフセット量
#define PICKREGIONPIXELCOUNT	( 1 + 2 * PICKREGIONOFFSET ) * ( 1 + 2 * PICKREGIONOFFSET )	// ピック領域のピクセル数

// Render Mode
enum ERENDERMODE
{
	RM_UNDEFINED = 0,
	RM_RENDER,			// 通常描画
	RM_PICK_ELEMENTTYPE,// ピック描画（要素タイプ）
	RM_PICK_ELEMENTID,	// ピック描画（要素番号）
};

enum ERENDERELEMENTTYPE
{
	RET_UNDEFINED = 0,
	RET_POINT,
	RET_LINE,
	RET_FACE,
};

class COpenGLPickView : public COpenGLTrackView
{
	// メンバ変数
private:
	GLuint			m_uiTextureID;
	GLuint			m_uiRenderBufferID;
	GLuint			m_uiFrameBufferID;
	unsigned int	m_auiName_picked[NAMEARRAYSIZE];	// ピックされた要素の名前列

	// メンバ関数
private:
	void	CreateFrameBuffer( int iWidth, int iHeight );
	void	DestroyFrameBuffer();
	void	UninitializeOpenGL();
	bool	RenderScene();
	void	RenderModel( ERENDERMODE eRenderMode );
	int		DoPicking( int x, int y );
	void	IdentifyPickRegionPixels( unsigned int uiCountPickRegionPixel, unsigned int  aauiNamePickRegionPixel[][NAMEARRAYSIZE] );

protected: // シリアル化からのみ作成します。
	COpenGLPickView();
	DECLARE_DYNCREATE(COpenGLPickView)

// 属性
public:
	COpenGLPickDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
//	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~COpenGLPickView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnRButtonUp( UINT nFlags, CPoint point );
};

#ifndef _DEBUG  // OpenGLPickView.cpp のデバッグ バージョン
inline COpenGLPickDoc* COpenGLPickView::GetDocument() const
   { return reinterpret_cast<COpenGLPickDoc*>(m_pDocument); }
#endif

