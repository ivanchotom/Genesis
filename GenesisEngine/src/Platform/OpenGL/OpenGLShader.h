#pragma once

#include "Renderer/Shader.h"
#include <glm/glm.hpp>


//TODO : REMOVE!
typedef unsigned int GLenum;

namespace GE {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float values);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		static GLenum ShaderTypeFromString(const std::string& type);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		void LegacyCompile(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:
		uint32_t m_RendererID;
		bool m_IsCompute = false;
	};
}