#include "ctpch.h"
#include "Application.h"

#include "Carrot/Events/ApplicationEvent.h"
#include "Carrot/Log.h"


namespace Carrot {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}

}