#include "Core/Engine.hpp"
#include "Helpers/EngineHelper.hpp"

int main() {
	Engine engine;
	engine.CreateWindow(1280, 720, "Game Prototype");
	EngineHelper::StartupScenes(engine);
	engine.Start();
    return 0;
}