#pragma once

#include <glm/glm.hpp>

namespace Hazel {

	class OrthographicCamera
	{
	public:
		//正射投影矩阵定义了一个类似立方体的平截头箱，它定义了一个裁剪空间，在这空间之外的顶点都会被裁剪掉
		//定义一个正射投影需要六个参数，定义着平截头的长宽高、远近平面
		OrthographicCamera(float left, float right, float bottom, float top);//?远近平面在哪里？
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
		float m_Rotation = 0.0f;//？为什么正射矩阵的rotation只有一个维度？
	};
}