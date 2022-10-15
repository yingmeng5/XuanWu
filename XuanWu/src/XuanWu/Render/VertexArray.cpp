#include "xwpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace XuanWu {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: XW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		XW_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}


}