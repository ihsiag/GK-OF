//
// OpenGLExtFuncs.h
//
#pragma once

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>

#ifdef OPENGLEXTFUNCS_C	// OpenGLExtFuncs.c����Include�����Ƃ��́A�ϐ���`�i���̂��`����j
#	define EXTERN
#else					// OpenGLExtFuncs.c�ȊO����Include�����Ƃ��́A�ϐ��錾�i���̂��`���Ȃ��j
#	define EXTERN	extern
#endif

// OpenGL�g���@�\�֐�

// Framebuffer
EXTERN	PFNGLBINDFRAMEBUFFERPROC			glBindFramebuffer;
EXTERN	PFNGLCHECKFRAMEBUFFERSTATUSPROC		glCheckFramebufferStatus;
EXTERN	PFNGLDELETEFRAMEBUFFERSPROC			glDeleteFramebuffers;
EXTERN	PFNGLFRAMEBUFFERTEXTURE2DPROC		glFramebufferTexture2D;
EXTERN	PFNGLFRAMEBUFFERRENDERBUFFERPROC	glFramebufferRenderbuffer;
EXTERN	PFNGLGENFRAMEBUFFERSPROC			glGenFramebuffers;

// Renderbuffer
EXTERN	PFNGLBINDRENDERBUFFERPROC			glBindRenderbuffer;
EXTERN	PFNGLDELETERENDERBUFFERSPROC		glDeleteRenderbuffers;
EXTERN	PFNGLGENRENDERBUFFERSPROC			glGenRenderbuffers;
EXTERN	PFNGLRENDERBUFFERSTORAGEPROC		glRenderbufferStorage;

// VertexBuffer
EXTERN	PFNGLGENBUFFERSPROC					glGenBuffers;
EXTERN	PFNGLBINDBUFFERPROC					glBindBuffer;
EXTERN	PFNGLBUFFERDATAPROC					glBufferData;
EXTERN	PFNGLDELETEBUFFERSPROC				glDeleteBuffers;

// �����������i�֐��|�C���^�Ɗ֐��̕R�Â��j
bool InitOpenGLExtFuncs();
