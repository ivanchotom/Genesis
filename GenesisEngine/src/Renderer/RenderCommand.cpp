#include "PCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GE {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

	

}



