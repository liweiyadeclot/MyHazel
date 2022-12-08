#include"hzpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	//��Ⱦ��Renderer�ṩ��Ⱦ���̵��������

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		//ͨ��camera��VP�����õ�ǰ���Ƴ�����VP
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