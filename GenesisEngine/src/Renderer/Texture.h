#pragma once

#include "main/Core.h"

namespace GE {

	enum class GENESIS_API TextureFormat
	{
		None = 0,
	    RGB = 1,
	    RGBA = 2,
	};

	class GENESIS_API Texture
	{
	public:
		~Texture() {}
	};

	class GENESIS_API Texture2D : public Texture
	{
	public:
		static Texture2D* Create(TextureFormat format, unsigned int width, unsigned int height);

		virtual TextureFormat GetFormat() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
	};
}