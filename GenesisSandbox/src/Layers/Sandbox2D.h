#pragma once

#include "main/Engine.h"

#include "Testing/ParticleTest.h"

class Sandbox2D : public GE::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override; // "Constructor" for layer
	virtual void OnDetach() override; // "Destructor"  for layer

	void OnUpdate(GE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(GE::Event& e) override;

private:
	GE::Ref<GE::Shader> m_FlatColorShader;
	GE::OrthographicCameraController m_CameraController;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f};
	GE::Ref<GE::VertexArray> m_SquareVA;

	GE::Ref<GE::FrameBuffer> m_FrameBuffer;

	GE::Ref<GE::Texture2D> m_CheckerboardTexture;
	GE::Ref<GE::Texture2D> m_SpriteSheet;
	GE::Ref<GE::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

	ParticleProps m_Particle;
	ParticleSystem m_ParticleSystem;


	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, GE::Ref<GE::SubTexture2D>> s_TextureMap;

}; 