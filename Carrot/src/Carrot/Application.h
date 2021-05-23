#pragma once

#include "Core.h"

#include "Window.h"
#include "Carrot/LayerStack.h"
#include "Carrot/Events/Event.h"
#include "Carrot/Events/ApplicationEvent.h"

#include "Carrot/Core/Timestep.h"

#include "Carrot/ImGui/ImGuiLayer.h"

#include "Carrot/Renderer/Shader.h"
#include "Carrot/Renderer/VertexArray.h"

#include "Carrot/Renderer/OrthographicCamera.h"

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

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}