#include "Panels/SceneHierarchyPanel.h"

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
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

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			// 左键点击空白区域，取消选中
			m_SelectionContext = {};
		}

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext) 
		{
			//如果选中了某个entity，则显示这个entity的属性
			DrawComponents(m_SelectionContext);
		}
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

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256]; // 局部缓冲，用于接受InputBox输入
			memset(buffer, 0, sizeof(buffer)); // 设置buffer的所有内容为0
			strcpy_s(buffer, sizeof(buffer), tag.c_str()); // buffer设置初值

			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<TransformComponent>()) 
		{

			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
			auto& transform = entity.GetComponent<TransformComponent>().Transform;
			ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

			ImGui::TreePop();
			}
						
		}

		if (entity.HasComponent<CameraComponent>())
		{

			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& cameraComponent = entity.GetComponent<CameraComponent>();
				auto& camera = cameraComponent.Camera;

				ImGui::Checkbox("Primary", &cameraComponent.Primary);

				
				const char* projectionTypeString[] = { "Perspective","Orthographic" };
				const char* currentProjectionTypeString = projectionTypeString[(int)camera.GetProjectionType()];

				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++) 
					{
						// 遍历所有投影类型，如果当前投影类型被选中了，则设置相机类型为当前类型
						bool isSelected = currentProjectionTypeString == projectionTypeString[i];
						if (ImGui::Selectable(projectionTypeString[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeString[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}

						if (isSelected) 
						{
							ImGui::SetItemDefaultFocus();// 下次启动app时，也默认选中这一项
						}
					}
					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float verticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
					if (ImGui::DragFloat("Vertical FOV", &verticalFov))
					{
						camera.SetPerspectiveVerticalFOV(glm::radians(verticalFov));
					}

					float orthNear = camera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &orthNear))
					{
						camera.SetPerspectiveNearClip(orthNear);
					}

					float orthoFar = camera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
					{
						camera.SetPerspectiveFarClip(orthoFar);
					}
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
					{
						camera.SetOrthographicSize(orthoSize);
					}

					float orthNear = camera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &orthNear))
					{
						camera.SetOrthographicNearClip(orthNear);
					}

					float orthoFar = camera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
					{
						camera.SetOrthographicFarClip(orthoFar);
					}

					ImGui::Checkbox("Fix Aspect Ratio", &cameraComponent.FixedAspectRatio);

				}


				ImGui::TreePop();
			}

		}
	}
}