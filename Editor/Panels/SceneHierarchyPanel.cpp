#include "Panels/SceneHierarchyPanel.h"

#include <string.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "glm/gtc/type_ptr.hpp"
#include "Kaleidoscope/Scene/Components.h"

namespace Kaleidoscope
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene> &context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene> &context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		m_Context->m_Registry.each(
			[&](auto entityID)
			{
				Entity entity{entityID, m_Context.get()};
				DrawEntityNode(entity);
			});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			// 左键点击空白区域，取消选中
			m_SelectionContext = {};
		}

		// 右键点击空白区域时弹出弹窗
		if (ImGui::BeginPopupContextWindow(0, 1| ImGuiPopupFlags_NoOpenOverItems))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
			{
				m_Context->CreateEntity("Empty Entity");
			}
			ImGui::EndPopup();

		}



		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			// 如果选中了某个entity，则显示这个entity的属性
			DrawComponents(m_SelectionContext);
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto &tag = entity.GetComponent<TagComponent>().Tag;

		// 1：当没有选中的物体时，选中当前， 2：点击箭头时展开
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;// 设置点击行的任意一个位置都可以选中该行
		bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false; // 设置标记
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
			{
				entityDeleted = true;
			}
			ImGui::EndPopup();

		}

		if (opened)
		{
			// 1：当没有选中的物体时，选中当前， 2：点击箭头时展开
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void *)9817239, flags, tag.c_str());
			if (opened)
			{
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		// 延迟删除
		if (entityDeleted) 
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity) 
			{
				m_SelectionContext = {};// 如果当前选中了这个entity，则清空选中
			}
		}
	}

	static void DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		// 自定义的Vec3组件
		
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];// 0是粗体，1是正常体

		// 相当于imgui的变量命名空间
		ImGui::PushID(label.c_str());

		// 使用imgui的网格布局
		ImGui::Columns(2);
		// 设置左边列
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());

		// 设置右边列
		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth()); // 自动分配宽度
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
		ImGui::PushFont(boldFont);// 设置按钮字体
		if (ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();											  // 不换行
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f"); // 双精度显示
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
		ImGui::PushFont(boldFont);// 设置按钮字体
		if (ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine(); // 不换行
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
		ImGui::PushFont(boldFont);// 设置按钮字体
		if (ImGui::Button("Z", buttonSize))
		{
			values.z = resetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine(); // 不换行
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}

	template<typename T,typename UIFunctions>
	static void DrawComponent(const std::string& name, Entity entity, UIFunctions uiFunction) 
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen 
											   | ImGuiTreeNodeFlags_Framed 
											   | ImGuiTreeNodeFlags_FramePadding 
											   | ImGuiTreeNodeFlags_SpanAvailWidth 
											   | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight,lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
				{
					removeComponent = true;
				}
				ImGui::EndPopup();
			}


			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
			{
				entity.RemoveComponent<T>();
			}
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto &tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];				   // 局部缓冲，用于接受InputBox输入
			memset(buffer, 0, sizeof(buffer)); // 设置buffer的所有内容为0
			// strcpy_s(buffer, sizeof(buffer), tag.c_str()); // 安全拷贝，strcpy_s是windows系统特有的版本
			// strlcpy(buffer, tag.c_str(), sizeof(buffer)); // 安全拷贝，strlcpy是MacOS支持的版本
			strcpy(buffer, tag.c_str()); // buffer设置初值

			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))// 名字前添加"##"隐藏这个label
			{
				tag = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		// 一个创建component按钮
		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("AddComponent");
		}

		if (ImGui::BeginPopup("AddComponent"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				m_SelectionContext.AddComponent<CameraComponent>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				m_SelectionContext.AddComponent<SpriteRendererComponent>();
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();


		DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
		{
			DrawVec3Control("Translation", component.Translation);
			glm::vec3 rotation = glm::degrees(component.Rotation);
			DrawVec3Control("Rotation", rotation);
			component.Rotation = glm::radians(rotation);
			DrawVec3Control("Scale", component.Scale, 1.0f);
		});


		DrawComponent<CameraComponent>("Camera", entity, [](auto& component)
		{
			auto& camera = component.Camera;

			ImGui::Checkbox("Primary", &component.Primary);

			const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];

			if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					// 遍历所有投影类型，如果当前投影类型被选中了，则设置相机类型为当前类型
					bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
					if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
					{
						currentProjectionTypeString = projectionTypeStrings[i];
						camera.SetProjectionType((SceneCamera::ProjectionType)i);
					}

					if (isSelected)
					{
						ImGui::SetItemDefaultFocus(); // 下次启动app时，也默认选中这一项
					}
				}
				ImGui::EndCombo();
			}

			if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
			{
				float perspectiveVerticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
				if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
				{
					camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));
				}

				float perspectiveNear = camera.GetPerspectiveNearClip();
				if (ImGui::DragFloat("Near", &perspectiveNear))
				{
					camera.SetPerspectiveNearClip(perspectiveNear);
				}

				float perspectiveFar = camera.GetPerspectiveFarClip();
				if (ImGui::DragFloat("Far", &perspectiveFar))
				{
					camera.SetPerspectiveFarClip(perspectiveFar);
				}
			}

			if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
			{
				float orthoSize = camera.GetOrthographicSize();
				if (ImGui::DragFloat("Size", &orthoSize))
				{
					camera.SetOrthographicSize(orthoSize);
				}

				float orthoNear = camera.GetOrthographicNearClip();
				if (ImGui::DragFloat("Near", &orthoNear))
				{
					camera.SetOrthographicNearClip(orthoNear);
				}

				float orthoFar = camera.GetOrthographicFarClip();
				if (ImGui::DragFloat("Far", &orthoFar))
				{
					camera.SetOrthographicFarClip(orthoFar);
				}

				ImGui::Checkbox("Fixd Aspect Ratio", &component.FixedAspectRatio);
			}

		});

		DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [](auto& component)
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
		});

	}
}