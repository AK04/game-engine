#pragma once

#ifdef CT_PLATFORM_WINDOWS
	#ifdef CT_BUILD_DLL
		#define CARROT_API __declspec(dllexport)
	#else 
		#define CARROT_API __declspec(dllimport)
	#endif
#else
	#error Carrot only supports Windows!
#endif

#define BIT(x) (1 << x)