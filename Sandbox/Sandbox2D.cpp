#include "Sandbox2D.h"
#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWCCCCCCWWWWWWWWWWW"
"WWWWWDDDDDDDDDDDDWWWWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWDDDDDDDDDDDDDDDDDDWWW"
"WWDDDDWWWDDDDDDDDDDDDWWW"
"WDDDDDWWWDDDDDDDDDDDDDWW"
"WWDDDDDDDDDDDDDDDDDDDWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWWDDDDDDDDDDDDDDWWWWW"
"WWWWWWDDDDDDDDDDDWWWWWWW"
"WWWWWWWDDDDDDDDDWWWWWWWW"
"WWWWWWWWWWDDDDWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW";

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
{
}

void Sandbox2D::OnAttach()
{
	KLD_PROFILE_FUNCTION();

	// m_CheckerboardTexture = Kaleidoscope::Texture2D::Create("/Users/crystalized/cpp_project/LearnEngine/Sandbox/assets/textures/Checkerboard.png");
	m_CheckerboardTexture = Kaleidoscope::Texture2D::Create("../Sandbox/assets/textures/Checkerboard.png");

	Kaleidoscope::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = Kaleidoscope::Framebuffer::Create(fbSpec);


#if define 0


	m_SpriteSheet = Kaleidoscope::Texture2D::Create("../Sandbox/assets/game/textures/RPGpack_sheet_2X.png");

	m_TextureStairs = Kaleidoscope::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 11 }, { 128, 128 });
	m_TextureTree = Kaleidoscope::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;
	s_TextureMap['D'] = Kaleidoscope::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
	s_TextureMap['W'] = Kaleidoscope::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });

	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
#endif // 0


}

void Sandbox2D::OnDetach()
{
	KLD_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Kaleidoscope::Timestep ts)
{
	KLD_PROFILE_FUNCTION();

	// Update

	m_CameraController.OnUpdate(ts);

	// Render
	// Reset stats here
	Kaleidoscope::Renderer2D::ResetStats();
	{
		KLD_PROFILE_SCOPE("Renderer Prep");
		m_Framebuffer->Bind();
		Kaleidoscope::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Kaleidoscope::RenderCommand::Clear();
	}


	// 4个Quad
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;
		KLD_PROFILE_SCOPE("Renderer Draw");

		Kaleidoscope::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Kaleidoscope::Renderer2D::DrawRotateQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Kaleidoscope::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Kaleidoscope::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		Kaleidoscope::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Kaleidoscope::Renderer2D::DrawRotateQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);

		Kaleidoscope::Renderer2D::EndScene();
		
		Kaleidoscope::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Kaleidoscope::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Kaleidoscope::Renderer2D::EndScene();
		
		m_Framebuffer->UnBind();
	}




#if define 0


	// 粒子系统
	if (Kaleidoscope::Input::IsMouseButtonPressed(KLD_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Kaleidoscope::Input::GetMousePosition();
		auto width = Kaleidoscope::Application::Get().GetWindow().GetWidth();
		auto height = Kaleidoscope::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	// 游戏材质
	Kaleidoscope::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			// 遍历2d地图，渲染s_TextureMap里已经设置过的材质（Dirt Water），其他地方的材质用m_TextureStairs
			char tileType = s_MapTiles[x + y * m_MapWidth];
			Kaleidoscope::Ref<Kaleidoscope::SubTexture2D> texture;
			if (s_TextureMap.find(tileType) != s_TextureMap.end())
			{
				texture = s_TextureMap[tileType];
			}
			else
			{
				texture = m_TextureStairs;
			}

			Kaleidoscope::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);

		}

	}

	//Kaleidoscope::Renderer2D::DrawQuad({0.0f, 0.0f, 0.5f}, {1.0f, 1.0f}, m_TextureStairs);
	//Kaleidoscope::Renderer2D::DrawQuad({1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}, m_TextureBarrel);
	//Kaleidoscope::Renderer2D::DrawQuad({-1.0f, 0.0f, 0.5f}, {1.0f, 2.0f}, m_TextureTree);
	Kaleidoscope::Renderer2D::EndScene();
#endif // 0

}

void Sandbox2D::OnImGuiRender()
{
	KLD_PROFILE_FUNCTION();

	static bool dockingEnabled = true;

	if (dockingEnabled)
	{

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
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
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
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}


		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				if (ImGui::MenuItem("Exit"))
				{
					Kaleidoscope::Application::Get().Close();
				}
				ImGui::EndMenu();
			}


			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");
		auto stats = Kaleidoscope::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));

		//uint32_t textureID = m_CheckerboardTexture->GetRenderID();
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 1280.0f,720.0f });
		ImGui::End();

		ImGui::End();
	}
	else
	{
		ImGui::Begin("Settings");
		auto stats = Kaleidoscope::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));

		uint32_t textureID = m_CheckerboardTexture->GetRenderID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f,256.0f });
		ImGui::End();
	}
}

void Sandbox2D::OnEvent(Kaleidoscope::Event& e)
{
	m_CameraController.OnEvent(e);
}