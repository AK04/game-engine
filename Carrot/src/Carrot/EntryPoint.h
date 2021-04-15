#pragma once

#ifdef CT_PLATFORM_WINDOWS

extern Carrot::Application* Carrot::CreateApplication();

int main(int argc, char** argv) {

	Carrot::Log::Init();
	CT_INFO("Heres some info");
	int a = 20;
	CT_WARN("warning = {0}", a);

	auto app = Carrot::CreateApplication();
	app->Run();
	delete app;

}

#endif