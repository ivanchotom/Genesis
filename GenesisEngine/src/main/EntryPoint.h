#pragma once

#ifdef GS_PLATFORM_WINDOWS

extern GE::Application* GE::CreateApplication();

int main(int argc, char** argv)
{
	GE::Log::Init();
	GE_CORE_WARN("InitialisedLog");
	int a = 5;
	GE_INFO("Hello! Var={0}", a);
	
	auto app = GE::CreateApplication();
	app->Run();
	delete app;
}

#endif
