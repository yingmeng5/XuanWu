#pragma once

#include "Core.h"

#include "Window.h"
#include "XuanWu/LayerStack.h"
#include "Events/Event.h"
#include "XuanWu/Events/ApplicationEvent.h"


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
	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


