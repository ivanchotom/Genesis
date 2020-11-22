#include "PCH.h"
#include "Application.h"

#include "Events/AppEvent.h"
#include "Log.h"
#include "GLFW/glfw3.h"

namespace GE {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2, 0.7, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
		
	}

}