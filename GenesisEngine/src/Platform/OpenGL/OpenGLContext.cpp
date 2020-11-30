#include "PCH.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GE {



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		GS_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GS_CORE_ASSERT(status, "Failed to initialize GLAD!")

		GE_CORE_INFO("OpenGL Info:");
		GE_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		GE_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		GE_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}