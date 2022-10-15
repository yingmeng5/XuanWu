#pragma once

#include "Core.h"

#include "Window.h"
#include "XuanWu/LayerStack.h"
#include "Events/Event.h"
#include "XuanWu/Events/ApplicationEvent.h"

#include "XuanWu/ImGui/ImGuiLayer.h"
#include "XuanWu/Render/Shader.h"
#include "XuanWu/Render/Buffer.h"
#include "XuanWu/Render/VertexArray.h"

namespace XuanWu {
	class XUANWU_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<VertexArray> m_SquareVAO;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


