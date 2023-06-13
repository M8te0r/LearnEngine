#pragma once
#include "Kaleidoscope/Core/Base.h"

namespace Kaleidoscope
{
	struct FramebufferSpecification 
	{
		uint32_t Width = 0, Height = 0;

		// FramebufferFormat Format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false; // 用于标记这个framebuffer是否用于SwapChain，false=glBindFramebuffer(0)
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

	};


}