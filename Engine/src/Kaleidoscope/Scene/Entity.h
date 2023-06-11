#pragma once
#include "Kaleidoscope/Scene/Scene.h"
#include "entt.hpp"

namespace Kaleidoscope
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;


		template<typename T,typename... Args>
		T& AddComponent(Args&&... args)
		{
			KLD_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			//std::forward会将输入的参数原封不动地传递到下一个函数中，这个“原封不动”指的是，如果输入的参数是左值，那么传递给下一个函数的参数的也是左值；如果输入的参数是右值，那么传递给下一个函数的参数的也是右值。
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			KLD_CORE_ASSERT(!HasComponent<T>(), "Entity dose not have component!");

			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() 
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			KLD_CORE_ASSERT(!HasComponent<T>(), "Entity dose not have component!");

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};


}