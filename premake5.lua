workspace "Genesis"
   architecture "x64"
   startproject "GenesisSandbox"

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
IncludeDir ["glm"] = "GenesisEngine/3rdParty/glm"
IncludeDir ["stb_image"] = "GenesisEngine/3rdParty/stb_image"





group "Dependencies"
      include "GenesisEngine/3rdParty/GLFW"
      include "GenesisEngine/3rdParty/Glad"
      include "GenesisEngine/3rdParty/ImGui"
	  
	  
group ""


 project "GenesisEngine"
      location "GenesisEngine"
      kind "StaticLib"
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
            "%{prj.name}/src/**.cpp",
			"%{prj.name}/3rdParty/stb_image/**.h",
			"%{prj.name}/3rdParty/stb_image/**.cpp",
			"%{prj.name}/3rdParty/glm/glm/**.hpp",
			"%{prj.name}/3rdParty/glm/glm/**.inl"
      }
	  
	  defines 
	  {
	        "_CRT_SECURE_NO_WARNINGS"
	  }

      includedirs 
      {
            "%{prj.name}/src",
            "%{prj.name}/3rdParty/spdlog/include",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}"
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


	  filter "configurations:Debug"
	     defines "GE_DEBUG"
		 runtime "Debug"
		 symbols "on"

	  filter "configurations:Release"
	     defines "GE_RELEASE"
		 runtime "Release"
		 optimize "on"

	  filter "configurations:Dist"
	     defines "GE_DIST"
		 runtime "Release"
		 optimize "on"


project "GenesisSandbox"
      location "GenesisSandbox"
	  kind "ConsoleApp"
	  language "C++"
	  cppdialect "C++17"
	  staticruntime "on"
	  
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
			"GenesisEngine/3rdParty",
			"%{IncludeDir.glm}"
	  }

	  links
	  {
	     "GenesisEngine"
	  }

	  filter "system:windows"
		  systemversion "latest"
	  

	  defines
	  {
	       "GS_PLATFORM_WINDOWS"
	  }

	  filter "configurations:Debug"
	     defines "GE_DEBUG"
		 runtime "Debug"
		 symbols "on"

	  filter "configurations:Release"
	     defines "GE_RELEASE"
		 runtime "Release"
		 optimize "on"

	  filter "configurations:Dist"
	     defines "GE_DIST"
		 runtime "Release"
		 optimize "on"