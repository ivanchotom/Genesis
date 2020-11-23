workspace "Genesis"
   architecture "x64"

   configurations
        {
		  "Debug",
		  "Release",
		  "Dist"

        }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir ["GLFW"] = "GenesisEngine/3rdParty/GLFW/include"

include "GenesisEngine/3rdParty/GLFW"

 project "GenesisEngine"
      location "GenesisEngine"
	  kind "SharedLib"
	  language "C++"
	  
	  targetdir ("bin/"  .. outputdir .. "/%{prj.name}")
	  objdir ("bin-init/"  .. outputdir .. "/%{prj.name}")

	  pchheader "PCH.h"
	  pchsource "GameEngine/src/PCH.cpp"

	  files
	    {
			"%{prj.name}/src/**.h",
        	"%{prj.name}/src/**.cpp"
	    }

	  includedirs 
	    {
	  
	        "%{prj.name}/src",
			"%{prj.name}/3rdParty/spdlog/include",
			"%{IncludeDir.GLFW}"
	    }
	  
	  links
	  { 
	  "GLFW",
	  "opengl32.lib"
	  }

	  filter "system:windows"
	      cppdialect "C++17"
		  staticruntime "On"
		  systemversion "latest"
	  

	  defines
	    {
	       "GS_PLATFORM_WINDOWS",
	       "GS_BUILD_DLL"
	    }

	  postbuildcommands
	    {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/GenesisSandbox")
	    }

	  filter "configurations:Debug"
	     defines "GE_DEBUG"
		 buildoptions "/MDd"
		 symbols "On"

	  filter "configurations:Release"
	     defines "GE_RELEASE"
		 buildoptions "/MD"
		 optimize "On"

	  filter "configurations:Dist"
	     defines "GE_DIST"
		 buildoptions "/MD"
		 optimize "On"


project "GenesisSandbox"
      location "GenesisSandbox"
	  kind "ConsoleApp"
	  language "C++"
	  
	  targetdir ("bin/"  .. outputdir .. "/%{prj.name}")
	  objdir ("bin-init/"  .. outputdir .. "/%{prj.name}")


	  files
	    {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
	    }

	  includedirs
	    {
			"GenesisEngine/3rdParty/spdlog/include",
			"GenesisEngine/src",
			"%{IncludeDir.GLFW}"
	    }

	  links
	    {
	     "GenesisEngine"
	    }

	  filter "system:windows"
	      cppdialect "C++17"
		  staticruntime "On"
		  systemversion "latest"
	  

	  defines
	    {
	       "GS_PLATFORM_WINDOWS"
	    }

	  filter "configurations:Debug"
	     defines "GE_DEBUG"
		 buildoptions "/MDd"
		 symbols "On"

	  filter "configurations:Release"
	     defines "GE_RELEASE"
		 buildoptions "/MD"
		 optimize "On"

	  filter "configurations:Dist"
	     defines "GE_DIST"
		 buildoptions "/MD"
		 optimize "On"