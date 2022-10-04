#include "xwpch.h"

#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace XuanWu {

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		:m_WindowHandle(window)
	{
		XW_CORE_ASSERT(m_WindowHandle, "Window handle is NULL!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		XW_CORE_ASSERT(status, "Failed to initialize Glad!");

		XW_CORE_INFO("OpenGL Info:");
		XW_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		XW_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		XW_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}