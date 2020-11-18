#pragma once

#include "Core.h"


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