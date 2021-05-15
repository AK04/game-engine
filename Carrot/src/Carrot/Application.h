#pragma once

#include "Core.h"

#include "Window.h"
#include "Carrot/LayerStack.h"
#include "Carrot/Events/Event.h"
#include "Carrot/Events/ApplicationEvent.h"

#include "Carrot/ImGui/ImGuiLayer.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}

