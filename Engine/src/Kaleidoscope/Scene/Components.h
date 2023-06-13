#pragma once

#include "glm/glm.hpp"

#include "Kaleidoscope/Scene/SceneCamera.h"
#include "Kaleidoscope/Scene/ScriptableEntity.h"


namespace Kaleidoscope
{
	/*
	* 组件类，用于ECS系统，每一个组件都是一个entity
	*
	*/
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

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();//函数指针
		void (*DestroyScript)(NativeScriptComponent*);//函数指针


		template<typename T>
		void Bind()
		{
			InstantiateScript = []() {return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->Instance; nsc->Instance = nullptr; };

		}
	};
}