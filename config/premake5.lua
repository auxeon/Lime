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

	files { 
		basepath.."%{prj.name}/**"
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
			basepath.."%{prj.name}/lib/SDL2-2.0.12/include",
			-- nlohmann json
			basepath.."%{prj.name}/lib",
		}
		-- doing it only for 64 bit 
		libdirs {
			basepath.."%{prj.name}/lib/SDL2-2.0.12/lib/x64/"
		}

		links {
			"SDL2",
			"SDL2main",
			"SDL2test",
			"SDL2.dll"
		}
		p = "%{targetdir}"
		postbuildcommands {
			"{COPY} %{prj.name}\\lib\\SDL2-2.0.12\\lib\\x64\\SDL2.dll %{cfg.buildtarget.directory}"
		}
	end

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols ("On")

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize ("On")
		
