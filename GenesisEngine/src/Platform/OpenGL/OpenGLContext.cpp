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
		GS_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GS_CORE_ASSERT(status, "Failed to initialize GLAD!")

		GE_CORE_INFO("OpenGL Info:");
		GE_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		GE_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		GE_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));

        #ifdef GS_ENABLE_ASSERTS
		       int versionMajor;
		       int versionMinor;
		       glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		       glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		       
		       GS_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "GENESIS requires at least OpenGL version 4.5!");
        #endif
	}

	void OpenGLContext::SwapBuffers()
	{
		GS_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}