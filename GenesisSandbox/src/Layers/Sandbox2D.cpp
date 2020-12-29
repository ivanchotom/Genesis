#include "PCH.h"
#include "Sandbox2D.h"

#include "ImGui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <chrono>

class Timer
{
	Timer(const char* name)
		: m_Name(name), m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

	
		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		std::cout << "Duration: " << (end - start) << "ms"<< std::endl;
	}

	
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
	bool m_Stopped;

};

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
    {

    }




void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = GE::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	
}

void Sandbox2D::OnUpdate(GE::Timestep ts)
{

	Timer timer("asdaf");
	
	//Update
	m_CameraController.OnUpdate(ts);

	//Render
	GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GE::RenderCommand::Clear();

	GE::Renderer2D::BeginScene(m_CameraController.GetCamera());

	GE::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	GE::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	GE::Renderer2D::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);

	GE::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	//Color
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(GE::Event& e)
{
	m_CameraController.OnEvent(e);
}

