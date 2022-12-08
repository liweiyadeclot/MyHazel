#pragma once

#include "Hazel/Window.h"
#include "Hazel/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace Hazel {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		//是否开启垂直同步？关闭后帧率将上升
		bool IsVSync() const override;

		//这是一个很powerful的函数，任何代码都可以通过
		//访问进程中的单例Application中的单例Window类对象，来
		//获得Window类中真正的Window类型
		//这里使用的是GLFW类型的窗口，也可能使用其他
		//可能的类型的窗口自
		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}