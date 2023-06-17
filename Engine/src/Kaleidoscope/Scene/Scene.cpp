#include "kldpch.h"
#include "Kaleidoscope/Scene/Scene.h"

#include "Kaleidoscope/Scene/Components.h"
#include "Kaleidoscope/Renderer/Renderer2D.h"

#include "glm/glm.hpp"

#include "Kaleidoscope/Scene/Entity.h"

namespace Kaleidoscope
{


	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create() ,this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();//确保使用auto& 不然值拷贝无法动态改变TagComponent本体
		tag.Tag = name.empty() ? "Entity" : name;
		
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Update scripts
		{
			// TODO: 需要迁移至Scene::OnScenePlay
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				if (!nsc.Instance) 
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity,this };
					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(ts);

			});
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform ;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform,camera] = view.get<TransformComponent,CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);


			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}

			Renderer2D::EndScene();
		}

		
	}
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize 非固定高宽比的Camera
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}
}