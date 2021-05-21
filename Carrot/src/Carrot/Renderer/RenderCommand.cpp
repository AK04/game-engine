#include "ctpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Carrot {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}