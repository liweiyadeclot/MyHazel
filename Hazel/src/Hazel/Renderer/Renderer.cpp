#include"hzpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	//渲染器Renderer提供渲染过程的最顶级抽象

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		//通过camera的VP来设置当前绘制场景的VP
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		//submit into render command queue
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}