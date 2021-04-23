workspace "Carrot"
    architecture "x64"

    configurations {
        "debug",
        "release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Carrot"
    location "Carrot"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }


    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
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