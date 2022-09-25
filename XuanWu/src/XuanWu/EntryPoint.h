#pragma once

#ifdef XW_PLATFORM_WINDOWS 

extern XuanWu::Application* XuanWu::CreateApplication();

int main(int argc, char** argv)
{
	XuanWu::Log::Init();

	XW_CORE_TRACE("Initialized Engine!");
	XW_INFO("Welcome !");

	auto app = XuanWu::CreateApplication();
	app->Run();
	delete app;
}

#endif // XW_PLATFORM_WINDOWS 