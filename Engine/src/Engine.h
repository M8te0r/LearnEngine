#pragma once

// 设置当前平台为macos
#define KLD_PLATFORM_MACOS

// 用于Sandbox测试引用的头文件
#include "Kaleidoscope/Application.h"
#include "Kaleidoscope/Layer.h"
#include "Kaleidoscope/Log.h"
#include "Kaleidoscope/Input.h"
#include "Kaleidoscope/KeyCodes.h"
#include "Kaleidoscope/ImGui/ImGuiLayer.h"

// = = = = = = = Renderer相关 = = = = = = =
#include "Kaleidoscope/Renderer/Renderer.h"
#include "Kaleidoscope/Renderer/RenderCommand.h"

#include "Kaleidoscope/Renderer/Buffer.h"
#include "Kaleidoscope/Renderer/Shader.h"
#include "kaleidoscope/Renderer/VertexArray.h"

#include "Kaleidoscope/Renderer/OrthographicCamera.h"
// = = = = = = = = = = = = = = = = = = = = =

// 入口
#include "Kaleidoscope/EntryPoint.h"
