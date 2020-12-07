#pragma once

#include "Renderer/RendererAPI.h"
#include "Renderer/Texture.h"

namespace GE {

	class GENESIS_API OpenGLTexture2D : public Texture2D
	{
		OpenGLTexture2D(TextureFormat format, unsigned int width, unsigned int height);
		~OpenGLTexture2D();

		virtual TextureFormat GetFormat() const { return m_Format; }
		virtual unsigned int GetWidth() const { return m_Width; }
		virtual unsigned int GetHeight() const { return m_Height; }
	private:
		RendererID m_RendererID;
		TextureFormat m_Format;
		unsigned int m_Width, m_Height;
	};
}