#include <XuanWu.h>

#include <glm/glm.hpp>
#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public XuanWu::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), camera(75.0f, (float)XuanWu::Application::Get().GetWindow().GetWidth() / (float)XuanWu::Application::Get().GetWindow().GetHeight(), 0.1f, 1000.0f)
	{
		m_VertexArray.reset(XuanWu::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.f, 0.f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.f, 1.0f, 0.f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.f, 0.5f, 1.0f, 1.0f
		};
		XuanWu::Ref<XuanWu::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(XuanWu::VertexBuffer::Create(vertices, sizeof(vertices)));

		XuanWu::BufferLayout layout = {
			{ XuanWu::ShaderDataType::Float3, "a_Position" },
			{ XuanWu::ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		XuanWu::Ref<XuanWu::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(XuanWu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		//ËÄ±ßÐÎ
		m_SquareVAO.reset(XuanWu::VertexArray::Create());
		float SquareVertex[] = {
			-0.75f, -0.75f, .0f, 0.0f, 0.0f,
			 0.75f, -0.75f, .0f, 1.0f, 0.0f, 
			 0.75f,  0.75f, .0f, 1.0f, 1.0f,
			-0.75f,  0.75f, .0f, 0.0f, 1.0f 		
		};
		m_VertexBuffer.reset(XuanWu::VertexBuffer::Create(SquareVertex, sizeof(SquareVertex)));
		m_VertexBuffer->SetLayout({
			{ XuanWu::ShaderDataType::Float3, "a_Position" },
			{ XuanWu::ShaderDataType::Float2, "a_Texture"} });
		m_SquareVAO->AddVertexBuffer(m_VertexBuffer);

		uint32_t SquareIndices[] = { 0, 1, 2, 2, 0, 3 };
		m_IndexBuffer.reset(XuanWu::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(m_IndexBuffer);


		//m_Shader = XuanWu::Shader::Create("Texture", "assets/shaders/Texture.vs", "assets/shaders/Texture.frag");
		auto textureShader = m_ShaderLibrary.Load("Texture", "assets/shaders/Texture.vs", "assets/shaders/Texture.frag");
		m_Texture = XuanWu::Texture2D::Create("assets/textures/Checkerboard.png");
		m_TextureLogo = XuanWu::Texture2D::Create("assets/textures/ChernoLogo.png");
		std::dynamic_pointer_cast<XuanWu::OpenGLShader>(textureShader)->setInt("u_Texture", 0);
	}

	void OnUpdate(XuanWu::Timestep ts) override
	{
		XW_TRACE("Delta Time£º{0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (XuanWu::Input::IsKeyPressed(XW_KEY_W))
			m_CameraPosition.y += m_CameraSpeed * ts;
		else if (XuanWu::Input::IsKeyPressed(XW_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed * ts;
		if (XuanWu::Input::IsKeyPressed(XW_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed * ts;
		else if (XuanWu::Input::IsKeyPressed(XW_KEY_D))
			m_CameraPosition.x += m_CameraSpeed * ts;
		
		//camera.OnUpdate(ts);

		XuanWu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		XuanWu::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(0.0f );

		XuanWu::Renderer::BeginScene(m_Camera);

		//----------------------ÇøÓò--------------------------------------------------------

		//m_Shader->Bind();

		auto textureShader = m_ShaderLibrary.Get("Texture");
		textureShader->Bind();

		m_Texture->Bind();
		XuanWu::Renderer::Submit(textureShader, m_SquareVAO);

		m_TextureLogo->Bind();
		XuanWu::Renderer::Submit(textureShader, m_SquareVAO);
		
		//Triangle
		//XuanWu::Renderer::Submit(m_Shader, m_VertexArray);


		//----------------------------------------------------------------------------------

		XuanWu::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(XuanWu::Event& event) override
	{
		//camera.OnEvent(event);
	}
private:
	XuanWu::ShaderLibrary m_ShaderLibrary;
	XuanWu::Ref<XuanWu::Shader> m_Shader;
	XuanWu::Ref<XuanWu::VertexArray> m_VertexArray;

	XuanWu::Ref<XuanWu::VertexArray> m_SquareVAO;

	XuanWu::Ref<XuanWu::Texture2D> m_Texture, m_TextureLogo;

	XuanWu::OrthographicCamera m_Camera;
	XuanWu::PerspectiveCamera camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;

	glm::vec3 m_SquareColor = { 0.1f, 0.5f, 0.2f };
};

class Sandbox : public XuanWu::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

XuanWu::Application* XuanWu::CreateApplication()
{
	return new Sandbox();
}