#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

#include <memory>
namespace Hazel {

	
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		
		//ͨ��vertexArray��drawÿһ֡
		//ͨ��uniform�����ü�����Ĳ��ʵ�
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};


}