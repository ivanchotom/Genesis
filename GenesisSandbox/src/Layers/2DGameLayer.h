#pragma once

#include "main/Engine.h"

#include "2DGame/Level.h"
#include <imgui/imgui.h>

class GameLayer : public GE::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(GE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(GE::Event& e) override;
	bool OnMouseButtonPressed(GE::MouseButtonPressedEvent& e);
	bool OnWindowResize(GE::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	GE::Scope<GE::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};
