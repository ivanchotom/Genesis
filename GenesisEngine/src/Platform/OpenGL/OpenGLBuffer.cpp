#include "PCH.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>


namespace GE {

	/////////////////////////////////////////////////////////////////////////
	//////////////////////// VertexBuffer ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		GS_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		GS_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void GE::OpenGLVertexBuffer::Bind() const
	{
		GS_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void GE::OpenGLVertexBuffer::Unbind() const
	{
		GS_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/////////////////////////////////////////////////////////////////////////
	//////////////////////// IndexBuffer ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		GS_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		GS_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void GE::OpenGLIndexBuffer::Bind() const
	{
		GS_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void GE::OpenGLIndexBuffer::Unbind() const
	{
		GS_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
