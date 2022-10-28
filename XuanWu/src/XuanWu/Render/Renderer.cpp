#include "xwpch.h"
#include "Renderer.h"

namespace XuanWu {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& model)
	{
		shader->Bind();
		shader->setMat4("u_ViewProjectionMatrix", m_SceneData->ViewProjectionMatrix);
		shader->setMat4("u_Model", model);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}