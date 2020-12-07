#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace GE {

	using RendererID = unsigned int;

	enum class GENESIS_API RendererAPIType
	{
		None,
		OpenGL
	};

	class GENESIS_API RendererAPI
	{
	public:
		
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

	    static RendererAPIType Current() { return s_CurrentRendererAPI;  }
	private:
		static RendererAPIType s_CurrentRendererAPI;
	};

}