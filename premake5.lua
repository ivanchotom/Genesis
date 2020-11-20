workspace "Genesis"
   architecture "x64"

   configurations
   {
		  "Debug",
		  "Release",
		  "Dist"

   }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 project "GenesisEngine"
      location "GenesisEngine"
	  kind "SharedLib"
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
	        "%{prj.name}src
			"%{prj.name}/3rdParty/spdlog/include"
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
		 symbols "On"

	  filter "configurations:Release"
	     defines "GE_RELEASE"
		 optimize "On"

	  filter "configurations:Dist"
	     defines "GE_DIST"
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
		 symbols "On"

	  filter "configurations:Release"
	     defines "GE_RELEASE"
		 optimize "On"

	  filter "configurations:Dist"
	     defines "GE_DIST"
		 optimize "On"