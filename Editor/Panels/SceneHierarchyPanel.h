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
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};


}