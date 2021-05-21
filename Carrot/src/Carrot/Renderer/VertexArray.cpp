#include "ctpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Carrot {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		CT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}