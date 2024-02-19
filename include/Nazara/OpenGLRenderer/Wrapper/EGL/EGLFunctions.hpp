// Copyright (C) 2024 Jérôme "SirLynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - OpenGL renderer"
// For conditions of distribution and use, see copyright notice in Export.hpp

// no header guards

#ifndef NAZARA_DOCGEN

#if !defined(NAZARA_OPENGLRENDERER_EGL_FUNC) || !defined(NAZARA_OPENGLRENDERER_EGL_FUNC_OPT)
#error You must define NAZARA_OPENGLRENDERER_EGL_FUNC and NAZARA_OPENGLRENDERER_EGL_FUNC_OPT before including this file
#endif

NAZARA_OPENGLRENDERER_EGL_FUNC(eglBindAPI, PFNEGLBINDAPIPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglChooseConfig, PFNEGLCHOOSECONFIGPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglCreateContext, PFNEGLCREATECONTEXTPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglCreatePbufferSurface, PFNEGLCREATEPBUFFERSURFACEPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglCreateWindowSurface, PFNEGLCREATEWINDOWSURFACEPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglDestroyContext, PFNEGLDESTROYCONTEXTPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglDestroySurface, PFNEGLDESTROYSURFACEPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglGetConfigAttrib, PFNEGLGETCONFIGATTRIBPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglGetDisplay, PFNEGLGETDISPLAYPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglGetError, PFNEGLGETERRORPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglGetProcAddress, PFNEGLGETPROCADDRESSPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglInitialize, PFNEGLINITIALIZEPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglMakeCurrent, PFNEGLMAKECURRENTPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglQueryString, PFNEGLQUERYSTRINGPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglSwapBuffers, PFNEGLSWAPBUFFERSPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglSwapInterval, PFNEGLSWAPINTERVALPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC(eglTerminate, PFNEGLTERMINATEPROC)

NAZARA_OPENGLRENDERER_EGL_FUNC_OPT(eglCreatePlatformWindowSurface, PFNEGLCREATEPLATFORMWINDOWSURFACEPROC)
NAZARA_OPENGLRENDERER_EGL_FUNC_OPT(eglCreatePlatformWindowSurfaceEXT, PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC)

#undef NAZARA_OPENGLRENDERER_EGL_FUNC
#undef NAZARA_OPENGLRENDERER_EGL_FUNC_OPT

#endif // NAZARA_DOCGEN
