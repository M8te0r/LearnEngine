#include "EditorLayer.h"
#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Kaleidoscope/Scene/SceneSerializer.h"

#include "Kaleidoscope/Utils/PlatformUtils.h"

#include "ImGuizmo.h"

#include "Kaleidoscope/Math/Math.h"

namespace Kaleidoscope
{

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f), m_SquareColor({0.2f, 0.3f, 0.8f, 1.0f})
	{
	}

	void EditorLayer::OnAttach()
	{
		KLD_PROFILE_FUNCTION();

		// m_CheckerboardTexture = Texture2D::Create("/Users/crystalized/cpp_project/LearnEngine/Sandbox/assets/textures/Checkerboard.png");
		m_CheckerboardTexture = Texture2D::Create("../Editor/assets/textures/Checkerboard.png");

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8,FramebufferTextureFormat::RED_INTEGER,FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		// 激活场景
		m_ActiveScene = CreateRef<Scene>();

		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

#if 0
		// 创建entity
		auto square = m_ActiveScene->CreateEntity("Green Square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

		auto redSquare = m_ActiveScene->CreateEntity("Red Square");
		redSquare.AddComponent<SpriteRendererComponent>(glm::vec4{1.0f, 0.0f, 0.0f, 1.0f});

		m_SquareEntity = square;

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
		m_CameraEntity.AddComponent<CameraComponent>();

		m_SecondCamera = m_ActiveScene->CreateEntity("Camera B");
		auto &cc = m_SecondCamera.AddComponent<CameraComponent>();
		cc.Primary = false;

		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				translation.x = rand() % 10 - 5.0f;
			}

			void OnDestroy()
			{
			}

			void OnUpdateRuntime(Timestep ts)
			{
				auto &tanslation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;

				if (Input::IsKeyPressed(Key::A))
				{
					tanslation.x -= speed * ts;
				}
				if (Input::IsKeyPressed(Key::D))
				{
					tanslation.x += speed * ts;
				}
				if (Input::IsKeyPressed(Key::W))
				{
					tanslation.y += speed * ts;
				}
				if (Input::IsKeyPressed(Key::S))
				{
					tanslation.y -= speed * ts;
				}
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

#endif

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

		
	}

	void EditorLayer::OnDetach()
	{
		KLD_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		KLD_PROFILE_FUNCTION();

		// Resize
		if (
			FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// Update
		if (m_ViewportFocused)
		{
			m_CameraController.OnUpdate(ts);
		}

		m_EditorCamera.OnUpdate(ts);


		// Render
		// Reset stats here
		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
		RenderCommand::Clear();

		// Renderer2D::BeginScene(m_CameraController.GetCamera());

		// Update Scene
		// m_ActiveScene->OnUpdateRuntime(ts);
		m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

		auto[mx, my] = ImGui::GetMousePos(); // 获取鼠标的绝对坐标
		mx -= m_ViewportBounds[0].x; // 使得Editor的viewport视窗左上角相对于鼠标的坐标是[0,0]
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my; // 翻转鼠标的y轴坐标，鼠标坐标系的原点在屏幕左下角
		int mouseX = (int)mx;
		int mouseY = (int)my;

		if(mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY); // 从frambuffer的attachment1里面读取数据
			KLD_CORE_WARN("Pixel Data = {0}", pixelData);
		}


		m_Framebuffer->UnBind();
	}

	void EditorLayer::OnImGuiRender()
	{
		KLD_PROFILE_FUNCTION();

		// If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
		// In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
		// In this specific demo, we are not using DockSpaceOverViewport() because:
		// - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
		// - we allow the host window to have padding (when opt_padding == true)
		// - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
		// TL;DR; this demo is more complicated than what you would normally use.
		// If we removed all the options we are showcasing, this demo would become:
		//     void ShowExampleAppDockSpace()
		//     {
		//         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		//     }

		static bool dockSpaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport *viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO &io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;//设置docking窗口的最小宽度

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;//设置docking窗口的最小宽度

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.

				if (ImGui::MenuItem("New", "Ctrl+N")) 
				{
					NewScene();
				}

				if (ImGui::MenuItem("Open...", "Ctrl+O")) 
				{
					OpenScene();

				}

				if (ImGui::MenuItem("Save As...", "Ctrl+Shifit+S")) 
				{
					SaveSceneAs();
				}


				if (ImGui::MenuItem("Exit"))
				{
					Application::Get().Close();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		/* 实体层级视窗 */
		m_SceneHierarchyPanel.OnImGuiRender();

		/* 属性操作视窗 */
		ImGui::Begin("Stats");
		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		/* viewport视窗 */
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
		ImGui::Begin("Viewport");
		auto viewportOffset = ImGui::GetCursorPos();



		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = {viewportPanelSize.x, viewportPanelSize.y};

		uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID(); // 将framebuffer像纹理一样贴在viewport视窗上
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
		
		// 获取窗口所在屏幕的最小边界和最大边界
		auto windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += viewportOffset.x;
		minBound.y += viewportOffset.y;

		ImVec2 maxBound = { minBound.x + windowSize.x , minBound.y + windowSize.y };
		m_ViewportBounds[0] = { minBound.x, minBound.y };
		m_ViewportBounds[1] = { maxBound.x, maxBound.y };

		// KLD_CORE_WARN("Min Bounds = {0}, {1}", m_ViewportBounds[0].x, m_ViewportBounds[0].y);
		// KLD_CORE_WARN("Max Bounds = {0}, {1}", m_ViewportBounds[1].x, m_ViewportBounds[1].y);

		
		// Gizmos
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();	// 获取当前控制面板上选中的entity
		if (selectedEntity && m_GizmoType != -1) 
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			// Camera
			// 使用entity创建的camera
			// auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
			// const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			// const glm::mat4& cameraProjection = camera.GetProjection();
			// glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

			// 使用Editor Camera创建的camera
			const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
			glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

			// Entity transform
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f;	// 移动或者缩放时，变化0.5f
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE) 
			{
				snapValue = 45.0f;	// 旋转时，变化45.0f
			}
			
			float snapValues[3] = { snapValue,snapValue,snapValue };

			// Manipulate our transform then render it
			ImGuizmo::Manipulate(glm::value_ptr(cameraView),
								 glm::value_ptr(cameraProjection), 
								 (ImGuizmo::OPERATION)m_GizmoType, 
								 ImGuizmo::LOCAL, 
								 glm::value_ptr(transform),
								 nullptr,
								 snap?snapValues:nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;	// 获取transform矩阵的最后一列
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}
		
		
		
		
		
		
		ImGui::End();
		ImGui::PopStyleVar();

		// 结束docking模式
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event &e)
	{
		m_CameraController.OnEvent(e);
		m_EditorCamera.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(KLD_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
		{
			return false;
		}

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);

		switch (e.GetKeyCode())
		{
			case Key::N:
			{
				if (control)
				{
					NewScene();
				}
				break;
			}

			case Key::O:
			{
				if (control)
				{
					OpenScene();
				}
				break;
			}

			case Key::S:
			{
				if (control && shift)
				{
					SaveSceneAs();
				}
				break;
			}

			// Gizmos
			case Key::Q:
			{
				m_GizmoType = -1;
				break;
			}
			case Key::W:
			{
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			}
			case Key::E:
			{
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			}
			case Key::R:
			{
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
				break;
			}
		}

	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OpenScene()
	{
#ifdef KLD_PLATFORM_WINDOWS
		std::optional<std::string> filepath = FileDialogs::OpenFile("Kaleidoscope Scene (*.kld)\0*.kld\0");
#endif // KLD_PLATFORM_WINDOWS

#ifdef KLD_PLATFORM_MACOS
		std::optional<std::string> filepath = FileDialogs::OpenFile("kld");
#endif // KLD_PLATFORM_MACOS


		if (filepath)
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);

			// 序列化当前场景	
			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(*filepath);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
#ifdef KLD_PLATFORM_WINDOWS
		std::optional<std::string> filepath = FileDialogs::SaveFile("Kaleidoscope Scene (*.kld)\0*.kld\0");
#endif // KLD_PLATFORM_WINDOWS

#ifdef KLD_PLATFORM_MACOS
		std::optional<std::string> filepath = FileDialogs::SaveFile("kld");
#endif // KLD_PLATFORM_MACOS

		if (filepath)
		{
			// 反序列化已经保存的场景
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(*filepath);
		}
	}

}