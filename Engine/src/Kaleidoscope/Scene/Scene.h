#pragma once

#include "entt.hpp"

#include "Kaleidoscope/Core/Timestep.h"

namespace Kaleidoscope
{
	class Entity;

	class Scene 
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);

		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;// registry是所有component和entity的容器

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;				// Entity是Scene的友元类，Entity可以使用Scene的成员函数
		friend class SceneSerializer;		// SceneSerializer是Scene的友元类，SceneSerializer可以使用Scene的成员函数
		friend class SceneHierarchyPanel;	// SceneHierarchyPanel是Scene的友元类，SceneHierarchyPanel可以使用Scene的成员函数
	};
}