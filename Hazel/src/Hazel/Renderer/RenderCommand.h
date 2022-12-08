#pragma once

#include "RendererAPI.h"

namespace Hazel {

	//rendercommdand do not multi command，将gl作最底层的封装
	class RenderCommand
	{

	public:
		inline static void SetClearColor(const glm::vec4& color) 
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		//glDraw
	

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};

}