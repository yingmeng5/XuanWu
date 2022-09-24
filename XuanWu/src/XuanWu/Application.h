#pragma once

#include "Core.h"

namespace XuanWu {
	class XUANWU_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


