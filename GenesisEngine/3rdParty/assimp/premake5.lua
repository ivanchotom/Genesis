project "Assimp"
	kind "StaticLib"
	location "build/"
	defines {
		"ASSIMP_BUILD_NO_C4D_IMPORTER", -- Cinema4D is MSVC only and needs some weird headers to work
		"OPENDDL_STATIC_LIBARY",
	}
	files {
		"3rdParty/assimp/code/**.cpp",
		"3rdParty/assimp/code/**.h",
		"3rdParty/assimp/contrib/irrXML/*.cpp",
		"3rdParty/assimp/contrib/irrXML/*.h",
		"3rdParty/assimp/contrib/unzip/*.c",
		"3rdParty/assimp/contrib/unzip/*.h",
		"3rdParty/assimp/contrib/zlib/*.c",
		"3rdParty/assimp/contrib/openddlparser/code/*.cpp",
		"3rdParty/assimp/contrib/poly2tri/poly2tri/**.cc",
		"3rdParty/assimp/contrib/clipper/*.cpp",
	}
	includedirs {
		"3rdParty/_conf/",
		"3rdParty/assimp/include/",
		"3rdParty/assimp/contrib/irrXML/",
		"3rdParty/assimp/contrib/rapidjson/include/",
		"3rdParty/assimp/contrib/openddlparser/include/",
		"3rdParty/assimp/contrib/unzip/",
		"3rdParty/assimp/",
		"3rdParty/zlib/",
	}
	removefiles {
		"3rdParty/assimp/code/Importer/IFC/IFCReaderGen_4.*",
	}

	filter "system:windows"
		buildoptions {
			"/bigobj",
		}
		defines {
			"_CRT_SECURE_NO_WARNINGS",
		}
		disablewarnings {
			"4065",
		}

