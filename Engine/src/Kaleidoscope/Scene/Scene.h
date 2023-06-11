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
	private:
		entt::registry m_Registry;// registry是所有component和entity的容器

		friend class Entity;
	};
}