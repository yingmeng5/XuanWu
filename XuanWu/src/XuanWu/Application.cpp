#include "xwpch.h"
#include "Application.h"

#include "XuanWu/Log.h"

#include "XuanWu/Render/Renderer.h"

#include "Input.h"
#include "KeyCode.h"

namespace XuanWu {

//#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		XW_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(XW_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());
		
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.f, 0.f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.f, 1.0f, 0.f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.f, 0.5f, 1.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		//ËÄ±ßÐÎ
		m_SquareVAO.reset(VertexArray::Create());
		float SquareVertex[] = {
			-0.75f, -0.75f, .0f, .0f, 0.6f, 1.0f, 1.0f,
			 0.75f, -0.75f, .0f, .0f, 0.6f, 1.0f, 1.0f,
			 0.75f,  0.75f, .0f, .0f, 0.6f, 1.0f, 1.0f,
			-0.75f,  0.75f, .0f, .0f, 0.6f, 1.0f, 1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(SquareVertex, sizeof(SquareVertex)));
		m_VertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float4, "a_Color"} });
		m_SquareVAO->AddVertexBuffer(m_VertexBuffer);

		uint32_t SquareIndices[] = { 0, 1, 2, 2, 0, 3 };
		m_IndexBuffer.reset(IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(m_IndexBuffer);

		std::string vertexFile = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;

			out vec4 t_Color;
			void main()
			{
				t_Color = a_Color;
				gl_Position = vec4(a_Pos, 1.0);
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

		m_Shader.reset(new Shader(vertexFile, FragmentFile));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(XW_BIND_EVENT_FN(Application::OnWindowClose));
		if (XuanWu::Input::IsKeyPressed(XW_KEY_ESCAPE))
			m_Running = false;
		//XW_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
		
	void Application::Run()
	{	
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_SquareVAO);

			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}