#include "PCH.h"

#include "main/Engine.h"


class ExampleLayer : public GE::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		

		if (GE::Input::IsKeyPressed(GE_KEY_TAB))
			GE_TRACE("Tab key is pressed");
	}

	void OnEvent(GE::Event& event) override
	{
		//GE_TRACE("{0}", event);
	}
};

class Sandbox : public GE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new GE::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

GE::Application* GE::CreateApplication()
{
	return new Sandbox;
}