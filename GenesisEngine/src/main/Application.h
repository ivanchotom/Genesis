#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace GE {

	class GENESIS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	Application* CreateApplication();

}