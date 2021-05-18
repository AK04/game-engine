#include "ctpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Carrot{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {

		switch (Renderer::GetAPI()) {
			case RendererAPI::None:   CT_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		CT_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;

	}


	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {

		switch (Renderer::GetAPI()) {
			case RendererAPI::None:   CT_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		CT_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;

	}

}