#pragma once

#ifdef GS_PLATFORM_WINDOWS

extern GE::Application* GE::CreateApplication();

int main(int argc, char** argv)
{
	printf("it works");
	auto app = GE::CreateApplication();
	app->Run();
	delete app;
}

#endif