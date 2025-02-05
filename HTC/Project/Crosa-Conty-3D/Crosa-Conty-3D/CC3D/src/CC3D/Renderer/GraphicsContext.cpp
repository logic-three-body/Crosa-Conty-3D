#include "cc3d_pch.h"
#include "CC3D/Renderer/GraphicsContext.h"

#include "CC3D/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace CC3D {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CC3D_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		CC3D_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}