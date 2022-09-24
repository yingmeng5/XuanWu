#pragma once

#ifdef XW_PLATFORM_WINDOWS 

extern XuanWu::Application* XuanWu::CreateApplication();

int main(int argc, char** argv)
{
	auto app = XuanWu::CreateApplication();
	app->Run();
	delete app;
}

#endif // XW_PLATFORM_WINDOWS 