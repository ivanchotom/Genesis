#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/AppEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "TimeStep.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include "Cameras/OrthographicCamera.h"


namespace GE {

	class GENESIS_API Application
	{
	public:
		Application(const std::string& name = "Genesis");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window;  }

		void Close();

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		//Timestep m_TimeStep;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};


	Application* CreateApplication();

}