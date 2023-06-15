#include "Panels/SceneHierarchyPanel.h"

#include "imgui.h"

#include "Kaleidoscope/Scene/Components.h"

namespace Kaleidoscope 
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		m_Context->m_Registry.each(
			[&](auto entityID)
			{
				Entity entity{ entityID,m_Context.get() };
				DrawEntityNode(entity);

				
			}
		);
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		//1：当没有选中的物体时，选中当前， 2：点击箭头时展开
		ImGuiTreeNodeFlags flags = ((m_SelectionContext==entity)? ImGuiTreeNodeFlags_Selected :0 )| ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked()) 
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			//1：当没有选中的物体时，选中当前， 2：点击箭头时展开
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
			{
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}
}