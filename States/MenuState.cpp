//
// Created by nedo on 21.03.2022.
//

#include "MenuState.hpp"
#include "../Helpers/DrawableHelper.hpp"
#include "../Helpers/CursorHelper.hpp"
#include "Tests/AnimationState.hpp"

void MenuState::Start() {
	screen.setSize({1280, 720});

	CursorHelper::UseCursorPack(Resources->GetCursorPack("CursorPack_Default"));
	CursorHelper::Set(EnginePtr, sf::Cursor::Arrow);

	background.setSize({1280, 720});
	background.setTexture(&Resources->GetTexture("Menu_Background"));

	if(EnginePtr->GetConfig().IsFirstLaunch())
		fade.FadeOut(sf::Color::Black, 5000);
}

void MenuState::Update(sf::Time delta) {

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		EnginePtr->AddState<AnimationState>();
		EnginePtr->PopState();
	}

	screenTexture = DrawableHelper::DrawWithShaders({&background}, {fishEyeShader}, ViewSize);
	screen.setTexture(&screenTexture);

	fade.Update(delta);
}

std::string MenuState::GetName() {
	return "Menu State";
}

void MenuState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(screen);
	target.draw(fade);
}
