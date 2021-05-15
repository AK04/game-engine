workspace "Carrot"
    startproject "Carrot"
    architecture "x64"

    configurations {
        "debug",
        "release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Carrot/vendor/GLFW/include"
IncludeDir["Glad"] = "Carrot/vendor/Glad/include"
IncludeDir["ImGui"] = "Carrot/vendor/imgui"
IncludeDir["glm"] = "Carrot/vendor/glm"

include "Carrot/vendor/GLFW"
include "Carrot/vendor/Glad"
include "Carrot/vendor/imgui"

project "Carrot"
    location "Carrot"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ctpch.h"
    pchsource "Carrot/src/ctpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines 
        {
            "CT_PLATFORM_WINDOWS",
            "CT_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "CT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "CT_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "CT_DIST"
        runtime "Release"
        optimize "on"

    
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }


    includedirs {
        "Carrot/vendor/spdlog/include;",
        "Carrot/src",
        "%{IncludeDir.glm}",
        "Carrot/vendor"
    }

    links {
        "Carrot"
    }
    
    filter "system:windows"
        systemversion "latest"

        defines 
        {
            "CT_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "CT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "CT_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "CT_DIST"
        runtime "Release"
        optimize "on"