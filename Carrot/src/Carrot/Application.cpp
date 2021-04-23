#include "Application.h"

#include "Carrot/Events/ApplicationEvent.h"
#include "Carrot/Log.h"


namespace Carrot {

	Application::Application() {


	}

	Application::~Application() {

	}

	void Application::Run() {

		WindowResizeEvent e(1280, 720);
		CT_TRACE(e);

		while (true);
	}

}