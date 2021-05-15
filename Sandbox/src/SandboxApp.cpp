#include <Carrot.h>

#include "imgui/imgui.h"

class ExampleLayer : public Carrot::Layer {
public:
	ExampleLayer()
		: Layer("Example") {

	}

	void OnUpdate() override {
		//CT_INFO("Example Layer: Update");

		if (Carrot::Input::IsKeyPressed(CT_KEY_TAB))
			CT_TRACE("Tab is pressed!");

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}


	void OnEvent(Carrot::Event& event) override {
		//CT_TRACE("{0}", event);
	}

};

class Sandbox : public Carrot::Application {

public:

	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}

};

Carrot::Application* Carrot::CreateApplication() {
	return new Sandbox();
}