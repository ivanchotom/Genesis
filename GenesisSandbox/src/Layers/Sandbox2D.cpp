#include "PCH.h"
#include "Sandbox2D.h"

#include "ImGui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	GS_PROFILE_FUNCTION();

	m_CheckerboardTexture = GE::Texture2D::Create("assets/textures/Checkerboard.png");
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
	{
		GS_PROFILE_SCOPE("Renderer Prep");
		GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GE::RenderCommand::Clear();
	}

	//Render Draw
	{
		GS_PROFILE_SCOPE("Renderer Draw");
		GE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		//GE::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		GE::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		GE::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		//GE::Renderer2D::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		GE::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{

	GS_PROFILE_FUNCTION();
	//Color
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(GE::Event& e)
{
	m_CameraController.OnEvent(e);
}

