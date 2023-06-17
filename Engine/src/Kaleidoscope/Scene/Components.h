#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
		TagComponent(const TagComponent &) = default;
		TagComponent(const std::string &tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
		glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
		glm::vec3 Scale = {1.0f, 1.0f, 1.0f};

		TransformComponent() = default;
		TransformComponent(const TransformComponent &) = default;
		TransformComponent(const glm::vec3 &translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, {1, 0, 0}) *
								 glm::rotate(glm::mat4(1.0f), Rotation.y, {0, 1, 0}) *
								 glm::rotate(glm::mat4(1.0f), Rotation.z, {0, 0, 1});

			return glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent &) = default;
		SpriteRendererComponent(const glm::vec4 &color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		// 是否是主摄像头
		bool Primary = true;		   // TODO: 这个属性需要迁移至Scene中来管理
		bool FixedAspectRatio = false; // 是否固定高宽比决定了这个camera更新的方式

		CameraComponent() = default;
		CameraComponent(const CameraComponent &) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity *Instance = nullptr;

		ScriptableEntity *(*InstantiateScript)();		// 函数指针
		void (*DestroyScript)(NativeScriptComponent *); // 函数指针

		template <typename T>
		void Bind()
		{
			InstantiateScript = []()
			{ return static_cast<ScriptableEntity *>(new T()); };
			DestroyScript = [](NativeScriptComponent *nsc)
			{delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}