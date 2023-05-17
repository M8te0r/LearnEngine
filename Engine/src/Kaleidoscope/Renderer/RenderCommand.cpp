#include "kldpch.h"
#include "Kaleidoscope/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Kaleidoscope
{
    RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
} // namespace Kaleidoscope
