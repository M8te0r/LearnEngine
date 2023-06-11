#include "kldpch.h"
#include "Kaleidoscope/Scene/Entity.h"

namespace Kaleidoscope
{
	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene) 
	{}

}