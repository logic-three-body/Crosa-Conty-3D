#pragma once
#include<memory>
// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define CC3D_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define CC3D_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define CC3D_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define CC3D_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define CC3D_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection


//for Window
///linking runtime library dynamically; 
///defined CC3D_ENABLE_ASSERTS if CC3D_DEBUG is on.
#ifdef CC3D_DEBUG
	#if defined(CC3D_PLATFORM_WINDOWS)
		#define CC3D_DEBUGBREAK() __debugbreak()
	#elif defined(CC3D_PLATFORM_LINUX)
		#include <signal.h>
		#define CC3D_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define CC3D_ENABLE_ASSERTS
#define CC3D_ENABLE_ASSERTS
#else
	#define CC3D_DEBUGBREAK()
#endif

///check certain conditons,log message
///if it fails,it would call debugbreak -> set a debug point on that line,to see what's wrong
#ifdef  CC3D_ENABLE_ASSERTS
	#define CC3D_ASSERT(x, ...) { if(!(x)) { CC3D_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CC3D_CORE_ASSERT(x, ...) { if(!(x)) { CC3D_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CC3D_ASSERT(x, ...)
	#define CC3D_CORE_ASSERT(x, ...)
#endif


//for Event.h
#define BIT(x) (1 << x)


///see more details about this:
///std::bind(&XXX,this,std::placeholders::_1)
///https://stackoverflow.com/questions/61649318/how-could-c-stdbind-return-value-assigned-to-stdfunction
#define CC3D_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace CC3D {

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
	template<typename T, typename ... Args>
	constexpr Ref<T> CastRef(Args&& ... args)
	{
		return std::dynamic_pointer_cast<T>(std::forward<Args>(args)...);
	}
}
