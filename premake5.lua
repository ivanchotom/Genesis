workspace "Genesis"
   architecture "x64"
   startproject "GenesisEditor"

   configurations
        {
          "Debug",
          "Release",
          "Dist"
        }

		flags
		{
			"MultiProcessorCompile"
		}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir ["GLFW"] = "GenesisEngine/3rdParty/GLFW/include"
IncludeDir ["Glad"] = "GenesisEngine/3rdParty/Glad/include"
IncludeDir ["ImGui"] = "GenesisEngine/3rdParty/ImGui"
IncludeDir ["glm"] = "GenesisEngine/3rdParty/glm"
IncludeDir ["EnTT"] = "GenesisEngine/3rdParty/EnTT/Include"
IncludeDir ["stb_image"] = "GenesisEngine/3rdParty/stb_image"
IncludeDir ["yaml_cpp"] = "GenesisEngine/3rdParty/yaml-cpp/include"
IncludeDir ["ImGuizmo"] = "GenesisEngine/3rdParty/ImGuizmo"





group "Dependencies"
      include "GenesisEngine/3rdParty/GLFW"
      include "GenesisEngine/3rdParty/Glad"
      include "GenesisEngine/3rdParty/ImGui"
	  include "GenesisEngine/3rdParty/yaml-cpp"
	  
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
	      "%{prj.name}/3rdParty/glm/glm/**.inl",
	      "%{prj.name}/3rdParty/ImGuizmo/ImGuizmo.h",
	      "%{prj.name}/3rdParty/ImGuizmo/ImGuizmo.cpp"
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
	      "%{IncludeDir.stb_image}",
	      "%{IncludeDir.EnTT}",
	      "%{IncludeDir.yaml_cpp}",
	      "%{IncludeDir.ImGuizmo}"
      }

      links
      { 
        "GLFW",
	    "Glad",
	    "yaml-cpp",
	    "ImGui",
	    "opengl32.lib"
	  
      }

	  filter "files:GenesisEngine/3rdParty/ImGuizmo/**.cpp"
	  flags  { "NoPCH" }


      filter "system:windows"
          systemversion "latest"
	  

      defines
      {
	       "GS_BUILD_DLL",
		   "GLFW_INCLUDE_NONE"
      }


	  filter "configurations:Debug"
	     defines "GS_DEBUG"
		 runtime "Debug"
		 symbols "on"

	  filter "configurations:Release"
	     defines "GS_RELEASE"
		 runtime "Release"
		 optimize "on"

	  filter "configurations:Dist"
	     defines "GS_DIST"
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
			"GenesisSandbox/src",
			"GenesisEngine/3rdParty",
			"%{IncludeDir.glm}",
			"%{IncludeDir.EnTT}"
	  }

	  links
	  {
	     "GenesisEngine"
	  }

	  filter "system:windows"
		  systemversion "latest"
	  
	  filter "configurations:Debug"
	     defines "GS_DEBUG"
		 runtime "Debug"
		 symbols "on"

	  filter "configurations:Release"
	     defines "GS_RELEASE"
		 runtime "Release"
		 optimize "on"

	  filter "configurations:Dist"
	     defines "GS_DIST"
		 runtime "Release"
		 optimize "on"

project "GenesisEditor"
      location "GenesisEditor"
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
			"GenesisEditor/src",
			"GenesisEngine/3rdParty",
			"%{IncludeDir.glm}",
			"%{IncludeDir.EnTT}"
	  }

	  links
	  {
	     "GenesisEngine"
	  }

	  filter "system:windows"
		  systemversion "latest"
	  
	  filter "configurations:Debug"
	     defines "GS_DEBUG"
		 runtime "Debug"
		 symbols "on"

	  filter "configurations:Release"
	     defines "GS_RELEASE"
		 runtime "Release"
		 optimize "on"

	  filter "configurations:Dist"
	     defines "GS_DIST"
		 runtime "Release"
		 optimize "on"