#pragma once
#include "main/Engine.h"
#include "Panels/SceneHierarchyPanel.h"

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
		Ref<Scene> m_ActiveScene;
		Entity m_SqareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		SceneHierarchyPanel m_SHPanel;

	private:
		bool m_PrimaryCamera = true;

		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 0, 0};

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		int m_GuizmoType = -1;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();

		void OpenScene();

		void SaveSceneAs();
		

	};
}