#pragma once

#include <memory>
#include "main/Core.h"
#include "Buffer.h"


// Past Ivan here : Vertex arrays apparently only exist for OpenGL , If ur doing any other rendering API you should not look for them

namespace GE {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}


		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)= 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};


}