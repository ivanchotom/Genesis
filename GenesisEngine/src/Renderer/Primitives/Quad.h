#pragma once

#include "Renderer/Texture.h"
#include "Renderer/SubTexture2D.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer2D.h"

namespace GE {

	class Quad
	{
	public :
		  ~Quad() = default;

		  static Ref<Quad> Create();

		  static void SetQuad(const std::string& name, const glm::mat4& value);
		  //Ref<Quad> GetQuad() const { return *m_Quad; }

		  static void QuadEndScene();
		  static void QuadStartBatch();
		  static void QuadFlush();

	      static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	      static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	      static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	      static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	      static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	      static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	     
	      static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, uint32_t entityID);
	      static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, uint32_t entityID, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);
	     
	    
	      static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	      static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	      static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	      static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	      static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	      static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		  //Stats
		  struct Statistics
		  {
			  uint32_t DrawCalls = 0;
			  uint32_t QuadCount = 0;

			  uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			  uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		  };


		  static void ResetStats();
          static Statistics GetStats();

	private:
		//Ref<Quad> m_Quad;
		//static QuadData s_Data;
	};



}