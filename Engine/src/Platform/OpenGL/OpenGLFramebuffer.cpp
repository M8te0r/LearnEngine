#include "kldpch.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include "glad/glad.h"

namespace Kaleidoscope {

	static const uint32_t s_MaxFramebufferSize = 8192;

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		:m_Specification(spec)
	{
		Invalidate();
	}


	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		// 检查是否有framebuffer，如果有，删除重新创建新的framebuffer
		if (m_RendererID) 
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}

		// 创建framebuffer
		//glCreateFramebuffers(1, &m_RendererID);// FIXME: OpenGL 4.5以上 
		
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		// 创建颜色信息附件
		//glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);// FIXME: OpenGL 4.5以上 
		glGenTextures(1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		// 创建深度信息附件
		//glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);// FIXME: OpenGL 4.5以上 
		glGenTextures(1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);

		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);// FIXME: OpenGL 4.2以上 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);// 注意这里一定要是GL_DEPTH_STENCIL_ATTACHMENT, 如果少了depth就不会保存深度信息


		// 检查framebuffer的状态
		KLD_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void OpenGLFramebuffer::Bind() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFramebuffer::UnBind() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize) 
		{
			KLD_CORE_WARN("Attempted to resize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_Specification.Width = width;
		m_Specification.Height = height;
		
		Invalidate();
	}


}