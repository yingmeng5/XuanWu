#include <XuanWu.h>

#include <glm/glm.hpp>
#include "imgui/imgui.h"

class ExampleLayer : public XuanWu::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(XuanWu::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.f, 0.f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.f, 1.0f, 0.f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.f, 0.5f, 1.0f, 1.0f
		};
		std::shared_ptr<XuanWu::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(XuanWu::VertexBuffer::Create(vertices, sizeof(vertices)));

		XuanWu::BufferLayout layout = {
			{ XuanWu::ShaderDataType::Float3, "a_Position" },
			{ XuanWu::ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<XuanWu::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(XuanWu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		//ËÄ±ßÐÎ
		m_SquareVAO.reset(XuanWu::VertexArray::Create());
		float SquareVertex[] = {
			-0.75f, -0.75f, .0f, .0f, 0.6f, 1.0f, 1.0f,
			 0.75f, -0.75f, .0f, .0f, 0.6f, 1.0f, 1.0f,
			 0.75f,  0.75f, .0f, .0f, 0.6f, 1.0f, 1.0f,
			-0.75f,  0.75f, .0f, .0f, 0.6f, 1.0f, 1.0f
		};
		m_VertexBuffer.reset(XuanWu::VertexBuffer::Create(SquareVertex, sizeof(SquareVertex)));
		m_VertexBuffer->SetLayout({
			{ XuanWu::ShaderDataType::Float3, "a_Position" },
			{ XuanWu::ShaderDataType::Float4, "a_Color"} });
		m_SquareVAO->AddVertexBuffer(m_VertexBuffer);

		uint32_t SquareIndices[] = { 0, 1, 2, 2, 0, 3 };
		m_IndexBuffer.reset(XuanWu::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(m_IndexBuffer);

		std::string vertexFile = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;

			out vec4 t_Color;
			void main()
			{
				t_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Pos, 1.0);
			}
		)";

		std::string FragmentFile = R"(
			#version 330 core
			layout(location = 0) out vec4 FragColor;

			in vec4 t_Color;
			void main()
			{
				FragColor = t_Color;
			}
		)";

		m_Shader.reset(new XuanWu::Shader(vertexFile, FragmentFile));
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

		XuanWu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		XuanWu::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(0.0f );

		XuanWu::Renderer::BeginScene(m_Camera);

		XuanWu::Renderer::Submit(m_Shader, m_SquareVAO);

		XuanWu::Renderer::Submit(m_Shader, m_VertexArray);

		XuanWu::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(XuanWu::Event& event) override
	{

	}
private:
	std::shared_ptr<XuanWu::Shader> m_Shader;
	std::shared_ptr<XuanWu::VertexArray> m_VertexArray;

	std::shared_ptr<XuanWu::VertexArray> m_SquareVAO;

	XuanWu::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;
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