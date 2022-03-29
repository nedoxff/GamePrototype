//
// Created by nedo on 22.03.2022.
//

#include "Fade.hpp"

void Fade::FadeIn(sf::Color color, float duration, const std::string &easing, int from, int to) {
	Set(color, duration, easing, from, to);
}

void Fade::FadeOut(sf::Color color, float duration, const std::string &easing, int from, int to) {
	Set(color, duration, easing, from, to);
}

void Fade::OnCompleted(const std::function<void()> &onCompleted) {
	this->onCompleted = onCompleted;
}

void Fade::Update(sf::Time delta) {
	if(completed) return;
	tween.step(delta.asMilliseconds());
}

void Fade::Set(sf::Color color, float duration, const std::string &easing, int from, int to) {
	completed = false;
	shape.setFillColor({color.r, color.g, color.b, static_cast<unsigned char>(from)});
	tween = tweeny::from(from).to(to).during(duration).via(easing);
	tween.onStep([this, to](int v){
		auto color = shape.getFillColor();
		shape.setFillColor({color.r, color.g, color.b, static_cast<unsigned char>(v)});
		if(v == to)
		{
			completed = true;
			if(onCompleted)
				onCompleted();
			return true;
		}
		return false;
	});
}

void Fade::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(shape);
}

Fade::Fade() {
	shape.setFillColor({0, 0, 0, 0});
	shape.setSize({1280, 720});
}
