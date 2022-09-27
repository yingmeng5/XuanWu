#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "XuanWu/Events/ApplicationEvent.h"
#include "Window.h"

namespace XuanWu {
	class XUANWU_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


