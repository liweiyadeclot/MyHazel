#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "Hazel/Renderer/VertexArray.h"
namespace Hazel {

	//class RendererAPI管理所有有关渲染的接口
	class RendererAPI
	{
	public:
		//enum class 声明的枚举成员只在class作用域内可见
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