#include <Carrot.h>

class Sandbox : public Carrot::Application {

public:

	Sandbox() {

	}

	~Sandbox() {

	}

};

Carrot::Application* Carrot::CreateApplication() {
	return new Sandbox();
}