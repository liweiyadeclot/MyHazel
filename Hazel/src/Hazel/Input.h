#pragma once
//������ѯ
//�����д���һ��ѧϰ
//���ڣ����ǵĳ������������ȫ������GLFW
//һ�пͻ������붼������GLFW keycode�ķ�ʽ
//ʵ�֣�����ζ���ڿͻ��ˣ�����ͬ����Ҫinclude
//glfw�⣬�������ǲ�ϣ�������ģ���app��ΨһӦ��
//�ұ�������Ķ�����ֻ�����ǵ�Hazel
#include "Hazel/Core.h"

namespace Hazel {
	class HAZEL_API Input
	{
	//������в������κ�data��ȫ�ֱ���s_Instance�������������
	public:
		//������Ȼʹ�õ���glfw��keycode���������ǻᴴ���Լ���keycode
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
		//�����Ľӿ�
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		//����ģʽ
		static Input* s_Instance;

	};
}