#pragma once
#include "glm/glm.hpp"
#include "Kaleidoscope/Scene/SceneCamera.h"


namespace Kaleidoscope 
{
	struct TagComponent 
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {}
	};

	struct TransformComponent 
	{
		glm::mat4 Transform {1.0f};

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			:Transform(transform) {}

		operator glm::mat4& () { return Transform; }// 隐式转换: TransformComponent = glm::mat4
		operator const glm::mat4& () const { return Transform; }// 隐式转换
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			:Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		// 是否是主摄像头
		bool Primary = true;//TODO: 这个属性需要迁移至Scene中来管理
		bool FixedAspectRatio = false;//是否固定高宽比决定了这个camera更新的方式

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
}