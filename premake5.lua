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
    kind "SharedLib"
    staticruntime "off"
    language "C++"

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
        cppdialect "C++17"
        systemversion "latest"

        defines 
        {
            "CT_PLATFORM_WINDOWS",
            "CT_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands 
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "CT_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "CT_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "CT_DIST"
        runtime "Release"
        optimize "On"

    
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }


    includedirs {
        "Carrot/vendor/spdlog/include;",
        "Carrot/src",
        "%{IncludeDir.glm}"
    }

    links {
        "Carrot"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines 
        {
            "CT_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "CT_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "CT_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "CT_DIST"
        runtime "Release"
        optimize "On"