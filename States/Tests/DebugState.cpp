//
// Created by nedo on 03.04.2022.
//

#include "DebugState.hpp"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui-SFML.h>
using namespace ImGui;

#include "WindowState.hpp"
#include "AnimationState.hpp"
#include "DialogState.hpp"

void DebugState::Start() {
	text.setCharacterSize(32);
	text.setFont(Resources->GetFont("95"));
	text.setString("Welcome to the debug menu.");
}

void DebugState::Update(sf::Time delta) {
	if(Button("Window UI Debug"))
		EnginePtr->AddState<WindowState>(true);
	if(Button("Dialog UI Debug"))
		EnginePtr->AddState<DialogState>(true);
	if(Button("Animation Debug"))
		EnginePtr->AddState<AnimationState>(true);
}

std::string DebugState::GetName() {
	return "[Debug]";
}

void DebugState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(text);
}
