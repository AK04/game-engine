#pragma once

#ifdef CT_PLATFORM_WINDOWS

extern Carrot::Application* Carrot::CreateApplication();

int main(int argc, char** argv) {

	Carrot::Log::Init();
	
	CT_PROFILE_BEGIN_SESSION("Startup", "CarrotProfile-Startup.json");
	auto app = Carrot::CreateApplication();
	CT_PROFILE_END_SESSION();

	CT_PROFILE_BEGIN_SESSION("Runtime", "CarrotProfile-Runtime.json");
	app->Run();
	CT_PROFILE_END_SESSION();

	CT_PROFILE_BEGIN_SESSION("Startup", "CarrotProfile-Shutdown.json");
	delete app;
	CT_PROFILE_END_SESSION();

}

#endif