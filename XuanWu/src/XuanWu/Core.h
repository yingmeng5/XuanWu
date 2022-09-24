#pragma once


#ifdef XW_PLATFORM_WINDOWS
	#ifdef XW_BUILD_DLL
		#define XUANWU_API __declspec(dllexport)
	#else
		#define XUANWU_API __declspec(dllimport)
	#endif // XW_BUILD_DLL
#else
	#error XuanWu only supports Windows!
#endif // XW_PLATFORM_WINDOWS
