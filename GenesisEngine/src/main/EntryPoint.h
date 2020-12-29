#pragma once

#ifdef GS_PLATFORM_WINDOWS

extern GE::Application* GE::CreateApplication();

int main(int argc, char** argv)
{
	GE::Log::Init();

	//Testing
	    //GE_CORE_WARN("InitialisedLog");
	    //int a = 5;
	    //GE_INFO("Hello! Var={0}", a);
	
	GS_PROFILE_BEGIN_SESSION("Startup", "GenesisProfile-Startup.json");
	auto app = GE::CreateApplication();
	GS_PROFILE_END_SESSION();

	GS_PROFILE_BEGIN_SESSION("Runtime", "GenesisProfile-Runtime.json");
	app->Run();
	GS_PROFILE_END_SESSION();

	GS_PROFILE_BEGIN_SESSION("Shutdown", "GenesisProfile-Shutdown.json");
	delete app;
	GS_PROFILE_END_SESSION();
}

#endif
