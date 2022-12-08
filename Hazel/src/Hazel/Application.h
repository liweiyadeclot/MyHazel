#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Renderer/Shader.h"

#include "Hazel/Renderer/Buffer.h"

#include "Hazel/Renderer/VertexArray.h"

#include "Hazel/Renderer/OrthographicCamera.h"

#include "Hazel/Core/Timestep.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;

	private:
		std::unique_ptr<Window> m_Window;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_BlueShader;

		//OrthographicCamera m_Camera;
		float m_LastFrameTime = 0.0f;

	};

	// To be defined in CLIENT
	Application* CreateApplication();

}