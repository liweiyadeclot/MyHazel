#pragma once
//输入轮询
//作用有待进一步学习
//现在，我们的程序对于输入完全依赖于GLFW
//一切客户端输入都必须以GLFW keycode的方式
//实现，这意味着在客户端，我们同样需要include
//glfw库，这是我们不希望看到的，在app中唯一应当
//且必须包含的东西就只有我们的Hazel
#include "Hazel/Core.h"

namespace Hazel {
	class HAZEL_API Input
	{
	//这个类中不包括任何data，全局变量s_Instance并不属于这个类
	public:
		//这里仍然使用的是glfw的keycode，后面我们会创建自己的keycode
		inline static bool IsKeyPressed(int keycord){
			return s_Instance->IsKeyPressedImpl(keycord);
		}

		inline static bool IsMouseButtonPressed(int button) {
			return s_Instance->IsMouseButtonPressedImpl(button);
		}

		inline static std::pair<float, float> GetMousPosition() {
			//return std::make_pair<float, float>(s_Instance->GetMouseXImpl(), s_Instance->GetMouseYImpl());
			return s_Instance->GetMousePositionImpl();
		}

		inline static float GetMouseX() {
			return s_Instance->GetMouseXImpl();
		}

		inline static float GetMouseY() {
			return s_Instance->GetMouseYImpl();
		}
	protected:
		//真正的接口
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		//单例模式
		static Input* s_Instance;

	};
}