#pragma once

#include "Core.h"

#include "Window.h"
#include "Carrot/LayerStack.h"
#include "Carrot/Events/Event.h"
#include "Carrot/Events/ApplicationEvent.h"

namespace Carrot {

	class CARROT_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		bool OnWindowClose(WindowCloseEvent& e);

		inline static Application& Get() { return *s_Instance;  }
		inline Window& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	Application* CreateApplication();

}

