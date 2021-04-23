#pragma once

#ifdef CT_PLATFORM_WINDOWS

extern Carrot::Application* Carrot::CreateApplication();

int main(int argc, char** argv) {

	Carrot::Log::Init();
	CT_CORE_INFO("Heres some info");
	int a = 5000;
	CT_CRITICAL("warning = {0}", a);

	auto app = Carrot::CreateApplication();
	app->Run();
	delete app;

}

#endif