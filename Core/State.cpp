//
// Created by nedo on 13.03.2022.
//

#include "State.hpp"
#include "Engine.hpp"


void State::Initialize(Engine* engine) {
	Resources = engine->GetResourceManager();
	ViewSize = engine->GetViewSize();
	EnginePtr = engine;
}