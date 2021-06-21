#include <Carrot.h>
#include <Carrot/Core/EntryPoint.h>

#include "GameLayer.h"

class Sandbox : public Carrot::Application
{
public:
	Sandbox()
	{
		PushLayer(new GameLayer());
	}

	~Sandbox()
	{
	}
};

Carrot::Application* Carrot::CreateApplication()
{
	return new Sandbox();
}