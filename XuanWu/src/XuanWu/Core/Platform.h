#pragma once

#include "GLFW/glfw3.h"

namespace XuanWu {

	class Platform
	{
	public:
		static float GetTime() { return static_cast<float>(glfwGetTime()); }
	};
}