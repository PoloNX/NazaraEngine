// Copyright (C) 2024 Jérôme "SirLynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - OpenGL renderer"
// For conditions of distribution and use, see copyright notice in Export.hpp


namespace Nz
{
	inline OpenGLWindowFramebuffer::OpenGLWindowFramebuffer(OpenGLSwapchain& renderWindow) :
	OpenGLFramebuffer(FramebufferType::Window),
	m_renderWindow(renderWindow)
	{
	}
}

