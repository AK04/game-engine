#pragma once

#ifdef CT_PLATFORM_WINDOWS

extern Carrot::Application* Carrot::CreateApplication();

int main(int argc, char** argv) {

	printf("Hello there");
	auto app = Carrot::CreateApplication();
	app->Run();
	delete app;

}

#endif