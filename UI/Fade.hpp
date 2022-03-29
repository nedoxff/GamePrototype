//
// Created by nedo on 22.03.2022.
//

#ifndef GAMEPROTOTYPE_FADE_HPP
#define GAMEPROTOTYPE_FADE_HPP

#include <SFML/Graphics.hpp>
#include <tweeny.h>

class Fade: public sf::Drawable {
public:
	Fade();
	void FadeIn(sf::Color color, float duration, const std::string& easing = "linear", int from = 0, int to = 255);
	void FadeOut(sf::Color color, float duration, const std::string& easing = "linear", int from = 255, int to = 0);
	void OnCompleted(const std::function<void()> &onCompleted);
	void Update(sf::Time delta);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	void Set(sf::Color color, float duration, const std::string& easing, int from, int to);
	bool completed = true;
	std::function<void()> onCompleted;
	sf::RectangleShape shape;
	tweeny::tween<int> tween;
};


#endif //GAMEPROTOTYPE_FADE_HPP
