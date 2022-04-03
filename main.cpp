#include "Core/Engine.hpp"
#include "Helpers/EngineHelper.hpp"
#include "Helpers/WindowsHelper.hpp"

int main() {
	WindowsHelper::OnStartup();

	Engine engine;
	engine.CreateWindow(1280, 720, "Game Prototype");
	EngineHelper::StartupScenes(engine);
	engine.Start();

	WindowsHelper::OnShutdown();
    return 0;
}