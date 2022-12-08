#pragma once

#include <glm/glm.hpp>

namespace Hazel {

	class OrthographicCamera
	{
	public:
		//����ͶӰ��������һ�������������ƽ��ͷ�䣬��������һ���ü��ռ䣬����ռ�֮��Ķ��㶼�ᱻ�ü���
		//����һ������ͶӰ��Ҫ����������������ƽ��ͷ�ĳ���ߡ�Զ��ƽ��
		OrthographicCamera(float left, float right, float bottom, float top);//?Զ��ƽ�������
		OrthographicCamera(){}
		const glm::vec3& GetPosition() const { return m_Position; }
		float getRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3& position) {
			m_Position = position;
			RecalculateViewMatrix();
		}

		void SetRotation(float rotation) {
			m_Rotation = rotation;
			RecalculateViewMatrix();
		}

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;


		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
		float m_Rotation = 0.0f;//��Ϊʲô��������rotationֻ��һ��ά�ȣ�
	};
}