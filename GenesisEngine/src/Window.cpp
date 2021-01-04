#include "PCH.h"
#include "Window.h"

#ifdef GS_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace GE
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef GS_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}