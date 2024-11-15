#pragma once

#include "Kaleidoscope/Core/Base.h"
#include "Kaleidoscope/Scene/Scene.h"
#include "Kaleidoscope/Scene/Entity.h"

namespace Kaleidoscope 
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);
		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();
		Entity GetSelectedEntity()const 
		{
			return m_SelectionContext;
		}
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};


}