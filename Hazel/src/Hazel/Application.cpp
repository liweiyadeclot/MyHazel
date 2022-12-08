#include "hzpch.h"
#include "Application.h"


#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

#include "Hazel/Renderer/Renderer.h"
 
#include "Hazel//Renderer/OrthographicCamera.h"


namespace Hazel {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		//回调函数就是用OnEvent(目前只是Log一条信息)
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false);
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			//update time
			float time = (float)glfwGetTime();//Platform::GetTime(), glfw just for windows
			Timestep timestep = time - m_LastFrameTime;//auto cast
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				//对于ImGuiLayer对OnImGuiRender有重载定义，而对于其他Layer函数体都为空
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		//使用创建好的dispatch
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//HZ_CORE_INFO("{0}", e);

		int i = 0;
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			//it--;
			(*--it)->OnEvent(e);
			
			if (e.Handled)
				break;
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}