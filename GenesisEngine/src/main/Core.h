#pragma once

#ifdef GS_PLATFORM_WINDOWS
       #ifdef GS_BUILD_DLL
              #define GENESIS_API __declspec(dllexport)
       #else
               #define GENESIS_API __declspec(dllimport)
       #endif
#else 
       #error Game Engine only supports Windows!
#endif // GS_PLATFORM_WINDOWS

#ifdef GS_ENABLE_ASSERTS
       #define GS_ASSERT(x, ...) { if(!(x)) { GS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
       #define GS_CORE_ASSERT(x, ...) { if(!(x)) { GS_CORE_ERROR("Assertion failed:{0}", __VA_ARGS__); __debugbreak(); } }
#else
       #define GS_ASSERT (x, ...)
       #define GS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
