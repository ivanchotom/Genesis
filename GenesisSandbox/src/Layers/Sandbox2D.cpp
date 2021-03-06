
#include "Sandbox2D.h"

#include "ImGui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <chrono>

static const uint32_t s_MapWidth = 24;

static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWDDDDDWWWWWWWWWWW"
"WWWWWDDDDDDDDDDDDWWWWWWW"
"WWWWDDDDDDDDDDWWWDDDWWWW"
"WWWWWDDDDDDDDDDDDDDWWWWW"
"WWWWDDDDDDDDDDDDDDDWWWWW"
"WWWWWDDDWWWDDDDDDDWWWWWW"
"WWWWWDDDDDDDDDDDDDDWWWWW"
"WWWWWDDDDDDDWWWWDDDWWWWW"
"WWWWWWWDDDDDDDDDDWWWWWWW"
"WWWWWWWWWDDDDDDWWWWWWWWW"
"WWWWWWWWWWWDDDWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
;


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	GS_PROFILE_FUNCTION();

	m_CheckerboardTexture = GE::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = GE::Texture2D::Create("assets/kenney/rpg/Spritesheet/RPGpack_sheet_2X.png");
	
	m_TextureBarrel = GE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 11 }, { 128, 128 });
	m_TextureTree = GE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, {1, 2});
	

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;
	s_TextureMap['W'] = GE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });
	s_TextureMap['D'] = GE::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, {128, 128} );

	// Particle
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach()
{
	GS_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(GE::Timestep ts)
{

	GS_PROFILE_FUNCTION();
	
	//Update
	m_CameraController.OnUpdate(ts);
	


	//Render Prep
	GE::Renderer2D::ResetStats();
	{
		GS_PROFILE_SCOPE("Renderer Prep");
		GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GE::RenderCommand::Clear();
	}


#if OLD_PATH
	//Render Draw
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		GS_PROFILE_SCOPE("Renderer Draw");
		GE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		GE::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		GE::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		GE::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		GE::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f}, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		GE::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation) , m_CheckerboardTexture, 20.0f);
		GE::Renderer2D::EndScene();

		GE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				GE::Renderer2D::DrawQuad({x, y}, { 0.45f, 0.45f }, color);
			}
		}
		GE::Renderer2D::EndScene();
	}
#endif
	if (GE::Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = GE::Input::GetMousePosition();
		auto width = GE::Application::Get().GetWindow().GetWidth();
		auto height = GE::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 50; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	GE::Renderer2D::BeginScene(m_CameraController.GetCamera());

	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * m_MapWidth];
			GE::Ref<GE::SubTexture2D> texture;
			if (s_TextureMap.find(tileType) != s_TextureMap.end())
				texture = s_TextureMap[tileType];
			else
				texture = m_TextureBarrel;

			GE::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
		}
	}


	//GE::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureStairs);
	//GE::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureBarrel);
	//GE::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.5f }, { 1.0f, 2.0f }, m_TextureTree);
	GE::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{

	GS_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = GE::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
	
}

void Sandbox2D::OnEvent(GE::Event& e)
{
	m_CameraController.OnEvent(e);
}

