#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "Hazel/Renderer/VertexArray.h"
namespace Hazel {

	//class RendererAPI���������й���Ⱦ�Ľӿ�
	class RendererAPI
	{
	public:
		//enum class ������ö�ٳ�Աֻ��class�������ڿɼ�
		enum class API
		{
			None = 0, OpenGL = 1
		};

	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		//glDraw
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }//?
	private:
		static API s_API;

	};
}