#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = XuanWu::VertexArray::Create();

	float vertices[] = {
		-0.75f, -0.75f, .0f, 0.0f, 0.0f,
		0.75f, -0.75f, .0f, 1.0f, 0.0f,
		0.75f,  0.75f, .0f, 1.0f, 1.0f,
		-0.75f,  0.75f, .0f, 0.0f, 1.0f
	};

	XuanWu::Ref<XuanWu::VertexBuffer> squareVB;
	squareVB.reset(XuanWu::VertexBuffer::Create(vertices, sizeof(vertices)));
	squareVB->SetLayout({
		{XuanWu::ShaderDataType::Float3, "a_Position"},
		{XuanWu::ShaderDataType::Float2, "a_Texture"}
		});

	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
	XuanWu::Ref<XuanWu::IndexBuffer> squareIB;
	squareIB.reset(XuanWu::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_Shader = XuanWu::Shader::Create("Texture", "assets/shaders/Texture.vs", "assets/shaders/Texture.frag");
	m_Texture = XuanWu::Texture2D::Create("assets/textures/ChernoLogo.png");
	std::dynamic_pointer_cast<XuanWu::OpenGLShader>(m_Shader)->setInt("u_Texture", 0);
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(XuanWu::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	XuanWu::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
	XuanWu::RenderCommand::Clear();

	XuanWu::Renderer::BeginScene(m_CameraController.GetCamera());

	m_Texture->Bind();
	XuanWu::Renderer::Submit(m_Shader, m_SquareVA);

	XuanWu::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(XuanWu::Event& event)
{
	m_CameraController.OnEvent(event);
}
