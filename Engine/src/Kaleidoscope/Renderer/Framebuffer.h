#pragma once
#include "Kaleidoscope/Core/Base.h"

namespace Kaleidoscope
{
	struct FramebufferSpecification 
	{
		uint32_t Width, Height;

		// FramebufferFormat Format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false; // 用于标记这个framebuffer是否用于SwapChain，false=glBindFramebuffer(0)
	};

	class Framebuffer
	{
	public:

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

	};


}