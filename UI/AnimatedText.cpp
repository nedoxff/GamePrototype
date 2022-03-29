//
// Created by nedo on 13.03.2022.
//

#include "AnimatedText.hpp"
#include "../Core/Logger.hpp"
#include "../Helpers/ObjectHelper.hpp"

void AnimatedText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(text);
}

AnimatedText::AnimatedText(const sf::Font& font, unsigned int size, sf::Vector2f position, const std::string &startText,
						   sf::Color color) {
	done = true;
	text.setFont(font);
	text.setCharacterSize(size);
	text.setPosition(position);
	text.setFillColor(color);
	center = false;
	centerX = false;
	centerY = false;

	this->startText = startText;
}

void AnimatedText::Update(sf::Time delta) {
	if (done) return;
	tween.step(delta.asMilliseconds());
	if (tween.progress() == 1.f) done = true;
}

void AnimatedText::Animate(const std::string &target, int time, const std::string &easing) {
	targetText = target;
	text.setString(startText);
	done = false;


	tween = tweeny::from(0).to(targetText.size()).during(time).via(easing);
	tween.onStep([this](int v){
		text.setString(startText + targetText.substr(0, v));
		if(center)
			ObjectHelper::Center(text, viewSize, centerX, centerY);
		return false;
	});
}

bool AnimatedText::IsDone() const {
	return done;
}

void AnimatedText::Center(sf::Vector2f viewSize, bool x, bool y) {
	center = true;
	centerX = x;
	centerY = y;
	this->viewSize = viewSize;
}
