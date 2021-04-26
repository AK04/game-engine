workspace "Carrot"
    architecture "x64"

    configurations {
        "debug",
        "release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Carrot/vendor/GLFW/include"

include "Carrot/vendor/GLFW"

project "Carrot"
    location "Carrot"
    kind "SharedLib"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ctpch.h"
    pchsource "Carrot/src/ctpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "CT_PLATFORM_WINDOWS",
            "CT_BUILD_DLL"
        }

        postbuildcommands 
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "CT_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CT_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CT_DIST"
        optimize "On"

    
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }


    includedirs {
        "Carrot/vendor/spdlog/include;",
        "Carrot/src"
    }

    links {
        "Carrot"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "CT_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "CT_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CT_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CT_DIST"
        optimize "On"