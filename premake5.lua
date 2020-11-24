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
IncludeDir ["Glad"] = "GenesisEngine/3rdParty/Glad/include"
IncludeDir ["ImGui"] = "GenesisEngine/3rdParty/ImGui"



include "GenesisEngine/3rdParty/GLFW"
include "GenesisEngine/3rdParty/Glad"
include "GenesisEngine/3rdParty/ImGui"


 project "GenesisEngine"
      location "GenesisEngine"
      kind "SharedLib"
      language "C++"
      cppdialect "C++17"
      staticruntime "on"
	  
      targetdir ("bin/"  .. outputdir .. "/%{prj.name}")
      objdir ("bin-init/"  .. outputdir .. "/%{prj.name}")

      pchheader "PCH.h"
      pchsource "GenesisEngine/src/PCH.cpp"

      files
      {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
      }

      includedirs 
      {
            "%{prj.name}/src",
            "%{prj.name}/3rdParty/spdlog/include",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}"
      }

      links
      { 
          "GLFW",
          "Glad",
		  "ImGui",
          "opengl32.lib"
      }

      filter "system:windows"
          systemversion "latest"
	  

      defines
      {
	       "GS_PLATFORM_WINDOWS",
	       "GS_BUILD_DLL",
		   "GLFW_INCLUDE_NONE"
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
            "GenesisEngine/src"
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