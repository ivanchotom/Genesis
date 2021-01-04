#pragma once
#include "main/Engine.h"

namespace GE {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override; // "Constructor" for layer
		virtual void OnDetach() override; // "Destructor"  for layer

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<FrameBuffer> m_FrameBuffer;

		Ref<Texture2D> m_CheckerboardTexture;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };


	};
}