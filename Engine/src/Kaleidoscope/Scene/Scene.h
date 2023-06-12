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

		void OnUpdate(Timestep ts);

		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		entt::registry m_Registry;// registry是所有component和entity的容器

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
	};
}