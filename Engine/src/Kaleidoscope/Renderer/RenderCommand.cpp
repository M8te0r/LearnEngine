#include "kldpch.h"
#include "Kaleidoscope/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Kaleidoscope
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
} // namespace Kaleidoscope
