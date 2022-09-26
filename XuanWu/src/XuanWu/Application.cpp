#include "Application.h"

#include "XuanWu/Log.h"
#include "XuanWu/Events/ApplicationEvent.h"

namespace XuanWu {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1920, 1080);
		XW_TRACE(e);
		while (true);
	}
}