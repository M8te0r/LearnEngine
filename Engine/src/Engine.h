#pragma once

// 设置当前平台为macos
//#define KLD_PLATFORM_MACOS

// 用于Sandbox测试引用的头文件
#include "Kaleidoscope/Core/Application.h"
#include "Kaleidoscope/Core/Layer.h"
#include "Kaleidoscope/Core/Log.h"

#include "Kaleidoscope/Core/Timestep.h"

#include "Kaleidoscope/Core/Input.h"
#include "Kaleidoscope/Core/KeyCodes.h"
#include "Kaleidoscope/Core/MouseCodes.h"
#include "Kaleidoscope/Renderer/OrthographicCameraController.h"

#include "Kaleidoscope/ImGui/ImGuiLayer.h"

#include "Kaleidoscope/Scene/Scene.h"
#include "Kaleidoscope/Scene/Entity.h"
#include "Kaleidoscope/Scene/ScriptableEntity.h"
#include "Kaleidoscope/Scene/Components.h"

// = = = = = = = Renderer相关 = = = = = = =
#include "Kaleidoscope/Renderer/Renderer.h"
#include "Kaleidoscope/Renderer/Renderer2D.h"
#include "Kaleidoscope/Renderer/RenderCommand.h"

#include "Kaleidoscope/Renderer/Buffer.h"
#include "Kaleidoscope/Renderer/Shader.h"
#include "Kaleidoscope/Renderer/Framebuffer.h"
#include "Kaleidoscope/Renderer/Texture.h"
#include "Kaleidoscope/Renderer/VertexArray.h"


#include "Kaleidoscope/Renderer/OrthographicCamera.h"
// = = = = = = = = = = = = = = = = = = = = =

// 入口
