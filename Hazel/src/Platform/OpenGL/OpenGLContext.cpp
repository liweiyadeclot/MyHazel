#include "hzpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "Handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");
		
		HZ_INFO("Renderer: ");
		HZ_INFO(noexcept(glGetString(GL_VENDOR)));
		//HZ_CORE_INFO("OpenGL Renderer: {0}", );

	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}