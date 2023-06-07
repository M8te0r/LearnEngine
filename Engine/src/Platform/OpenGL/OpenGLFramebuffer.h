#pragma once
#include "Kaleidoscope/Renderer/Framebuffer.h"
namespace Kaleidoscope 
{
	class OpenGLFramebuffer : public Framebuffer 
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }


		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }



	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FramebufferSpecification m_Specification;
	};
}