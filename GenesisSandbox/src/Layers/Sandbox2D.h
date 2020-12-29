#pragma once

#include "main/Engine.h"

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
	GE::Ref<GE::Texture2D> m_CheckerboardTexture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
}; 