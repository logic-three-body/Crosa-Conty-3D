#include "Application.h"



/////// Event System //////
#include "CC3D/Events/ApplicationEvent.h"
#include "CC3D/Events/KeyEvent.h"
#include "CC3D/Log.h"
///////////////////////////





namespace CC3D {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		WindowCloseEvent e1;
		KeyPressedEvent e2(1, 3);
		printf("Window Width: %d\n", e.GetWidth());
		if (e.IsInCategory(EventCategoryApplication))
		{
			/// #include "spdlog/fmt/ostr.h"
			/// this header file could use the ToString
			/// function in your class automatically
			/// if you don't want to include "spdlog/fmt/ostr.h"
			/// you need to write the *.ToString() by yourself as follow
			/// CC3D_TRACE(e.ToString())
			
			//CC3D_TRACE(e.ToString());
			CC3D_TRACE(e);
			CC3D_TRACE(e1);
			CC3D_TRACE(e2);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			CC3D_TRACE(e);
			CC3D_TRACE(e1);
			CC3D_TRACE(e2);
		}
		if (e2.IsInCategory(EventCategoryKeyboard))
		{
			CC3D_TRACE(e);
			CC3D_TRACE(e1);
			CC3D_TRACE(e2);
		}

		while (true)
		{

		}
	}
}