#pragma once
#include "entt.hpp"
#include "Kaleidoscope/Core/Timestep.h"

namespace Kaleidoscope
{
	class Scene 
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		//temp
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;// registry是所有component和entity的容器
	};
}