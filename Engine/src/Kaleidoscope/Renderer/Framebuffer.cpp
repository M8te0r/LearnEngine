#include "kldpch.h"
#include "Kaleidoscope/Renderer/Framebuffer.h"

#include "Kaleidoscope/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"
namespace Kaleidoscope {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) 
	{
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::API::OpenGL:

            return CreateRef<OpenGLFramebuffer>(spec);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
	}

}