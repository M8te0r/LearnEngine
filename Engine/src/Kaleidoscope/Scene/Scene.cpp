#include "kldpch.h"
#include "Kaleidoscope/Scene/Scene.h"

#include "Kaleidoscope/Scene/Components.h"
#include "Kaleidoscope/Renderer/Renderer2D.h"

#include "glm/glm.hpp"

namespace Kaleidoscope
{

	static void DoMath(const glm::mat4& transform)
	{

	}

	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		entt::entity entity = m_Registry.create();//entity是一个uint_32的编号

		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0));

		
		if(m_Registry.all_of<TransformComponent>(entity))
		TransformComponent& transform = m_Registry.get<TransformComponent>(entity);


		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view) 
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		}
#endif
	}

	Scene::~Scene()
	{

	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}