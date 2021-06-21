#pragma once

#include <memory>

#ifdef CT_PLATFORM_WINDOWS
	#if CT_DYNAMIC_LINK
		#ifdef CT_BUILD_DLL
			#define CARROT_API __declspec(dllexport)
		#else 
			#define CARROT_API __declspec(dllimport)
		#endif
	#else
		#define CARROT_API
	#endif
#else
	#error Carrot only supports Windows!
#endif

#ifdef CT_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif

#ifdef CT_ENABLE_ASSERTS
	#define CT_ASSERT(x, ...) { if(!(x) { CT_ERROR("Assertion failed {0} ", __VA_ARGS__); __debugbreak(); } }
	#define CT_CORE_ASSERT(x, ...) { if(!(x) { CT__CORE_ERROR("Assertion failed {0} ", __VA_ARGS__); __debugbreak(); } }
#else
	#define CT_ASSERT(x, ...)
	#define CT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Carrot {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}


}