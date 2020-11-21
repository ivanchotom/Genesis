#include "PCH.h"

#include "main/Engine.h"

class Sandbox : public GE::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

GE::Application* GE::CreateApplication()
{
	return new Sandbox;
}