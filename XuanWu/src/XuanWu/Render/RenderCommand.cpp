#include "xwpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace XuanWu {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}