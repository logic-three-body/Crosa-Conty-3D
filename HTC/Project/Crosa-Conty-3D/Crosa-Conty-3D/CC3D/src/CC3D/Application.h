#pragma once
#include "Core.h"//contain marcos
namespace CC3D {
	//class _declspec(dllexport) Application
	class CC3D_API Application //use CC3D_API as replacement of _declspec(dllexport) 
	{
	public:
		Application();
		virtual ~Application();//this class would be inherited by other class
		void run();
	};
}


