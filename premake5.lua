-- premake5.lua

basepath = "./"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Lime"
	configurations { 
	"Debug", 
	"Release" 
	}
	architecture "x86_64"

project "Lime"
	language ("C++")
	cppdialect ("C++17")
	
	targetdir (basepath.."%{prj.name}/builds/%{cfg.system}/bin/"..outputdir.."/%{prj.name}")
	objdir (basepath.."%{prj.name}/builds/%{cfg.system}/bin-int/"..outputdir.."/%{prj.name}")

	pchheader ("Pch.hpp")
	pchsource ("%{prj.name}/src/Pch.cpp")

	files { 
		basepath.."%{prj.name}/**"
		-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/core/inc/**.hpp",
		-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/core/inc/**.h",
		-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/fsbank/inc/**.hpp",
		-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/fsbank/inc/**.h",
		-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/studio/inc/**.hpp",
		-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/studio/inc/**.h"
	}


	if os.host() == "macosx" then
		kind ("WindowedApp")
		includedirs {
			basepath.."%{prj.name}/lib/SDL2.framework/Headers"
		}
		libdirs {
			basepath.."%{prj.name}/lib/**"
		}
		links {
			basepath.."%{prj.name}/lib/SDL2.framework"
		}
		buildoptions {
			"-F ../"..basepath.."lib"
		}
		p = path.getabsolute(basepath.."%{prj.name}/lib")
		linkoptions {
			"-F ../"..basepath.."lib",
			"-Wl -rpath "..p
		}
	end

	if os.host() == "windows" then
		kind ("WindowedApp")
	
		includedirs {
			-- include basepath
			basepath.."%{prj.name}",
			-- res containers
			basepath.."%{prj.name}/res",
			-- src 
			basepath.."%{prj.name}/src",
			-- lib includes
			-- SDL2
			basepath.."%{prj.name}/lib/SDL2-2.0.12/include",
			-- nlohmann json
			-- stb
			basepath.."%{prj.name}/lib",
			-- GLAD
			basepath.."%{prj.name}/lib/glad/include",
			basepath.."%{prj.name}/lib/glad/src",
			-- spdlog
			basepath.."%{prj.name}/lib/spdlog/include",
			-- glm
			basepath.."%{prj.name}/lib/glm-0.9.9.9",
			-- fmod
			basepath.."%{prj.name}/lib/fmod-2.01.06/api/core/inc/",
			basepath.."%{prj.name}/lib/fmod-2.01.06/api/fsbank/inc/",
			basepath.."%{prj.name}/lib/fmod-2.01.06/api/studio/inc/"



			-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/core/inc/**.h",
			-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/core/inc/**.hpp",
			-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/fsbank/inc/**.h",
			-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/fsbank/inc/**.hpp",
			-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/studio/inc/**.h",
			-- basepath.."{%prj.name}/lib/fmod-2.01.06/api/studio/inc/**.hpp"
		}
		-- doing it only for 64 bit 
		libdirs {
			-- SDL2
			basepath.."%{prj.name}/lib/SDL2-2.0.12/lib/x64/",
			-- fmod
			basepath.."%{prj.name}/lib/fmod-2.01.06/api/core/lib/x64/",
			basepath.."%{prj.name}/lib/fmod-2.01.06/api/fsbank/lib/x64/",
			basepath.."%{prj.name}/lib/fmod-2.01.06/api/studio/lib/x64/"
		}

		links {
			-- SDL2
			"SDL2",
			"SDL2main",
			"SDL2test",
			"SDL2.dll",
			-- OpenGL
			"opengl32",
			-- fmod
			"fmod_vc.lib",
			"fmodstudio_vc.lib",
			"fsbank_vc.lib"
		}
		p = "%{targetdir}"
		postbuildcommands {
			-- SDL2
			'{COPY} "%{prj.name}\\lib\\SDL2-2.0.12\\lib\\x64\\SDL2.dll" "%{cfg.buildtarget.directory}"',
			-- fmod
				-- core
			'{COPY} "%{prj.name}\\lib\\fmod-2.01.06\\api\\core\\lib\\x64\\fmod.dll" "%{cfg.buildtarget.directory}"',
				-- bank
			'{COPY} "%{prj.name}\\lib\\fmod-2.01.06\\api\\fsbank\\lib\\x64\\fsbank.dll" "%{cfg.buildtarget.directory}"',
			'{COPY} "%{prj.name}\\lib\\fmod-2.01.06\\api\\fsbank\\lib\\x64\\libfsvorbis64.dll" "%{cfg.buildtarget.directory}"',
			'{COPY} "%{prj.name}\\lib\\fmod-2.01.06\\api\\fsbank\\lib\\x64\\opus.dll" "%{cfg.buildtarget.directory}"',
				-- studio
			'{COPY} "%{prj.name}\\lib\\fmod-2.01.06\\api\\studio\\lib\\x64\\fmodstudio.dll" "%{cfg.buildtarget.directory}"'
		}

	end

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG" 
		optimize "On"
		
	filter "files:**.c"
		compileas "C++"

