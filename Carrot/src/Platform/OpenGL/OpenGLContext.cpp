#include "ctpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Carrot {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CT_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CT_CORE_ASSERT(status, "Failed to initialize Glad!");

		CT_CORE_INFO("OpenGL info:");
		CT_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		CT_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		CT_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}