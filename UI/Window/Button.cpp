//
// Created by nedo on 02.04.2022.
//

#include "Button.hpp"

void Button::ProcessEvent(Engine &engine, sf::Event &event) {
	if(!enabled) return;

	switch(event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			if(!clickable) return;
			if(event.mouseButton.button != sf::Mouse::Left) return;
			auto& window = *engine.GetWindow();
			auto bounds = animation.GetShape()->getGlobalBounds();
			auto mousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
			if(bounds.contains(static_cast<sf::Vector2f>(mousePos)))
			{
				clickable = false;
				animation.Play();
				if(Callbacks["Clicked"])
					Callbacks["Clicked"]();
			}
			break;
		}
		case sf::Event::MouseButtonReleased:
		{
			clickable = true;
			break;
		}
	}
}

void Button::Update(sf::Time delta) {
	animation.Update(delta);
	if(!animation.IsPlaying())
		animation.SetFrame(0);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(animation);
}

Button::Button(const Animation& animation, const sf::Vector2u& position) {
	this->animation = animation;
	this->animation.SetLoop(false);
	this->animation.SetFrame(0);
	this->animation.GetShape()->setPosition(static_cast<sf::Vector2f>(position));
	RequiredCallbacks = {"Clicked"};
}

void Button::SetEnabled(bool enabled) {
	this->enabled = enabled;
}

std::optional<const sf::Texture*> Button::GetCurrentTexture() {
	return animation.GetShape()->getTexture();
}
