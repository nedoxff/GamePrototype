#include "Core/Logger.hpp"
#include "Core/Engine.hpp"
#include "Helpers/EngineHelper.hpp"

int main() {
	Logger::Initialize();
	Engine engine(1280, 720, "Game Prototype");
	//engine.SetBackgroundColor({54,57,63});
	EngineHelper::StartupScenes(engine);
	engine.Start();
    return 0;
}