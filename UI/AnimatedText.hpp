//
// Created by nedo on 13.03.2022.
//

#ifndef GAMEPROTOTYPE_ANIMATEDTEXT_HPP
#define GAMEPROTOTYPE_ANIMATEDTEXT_HPP

#include <SFML/Graphics.hpp>
#include <tweeny.h>

class AnimatedText: public sf::Drawable {
public:
	AnimatedText() = default;
	AnimatedText(const sf::Font& font, unsigned int size, sf::Vector2f position, const std::string& startText = "", sf::Color color = sf::Color::White);
	void Update(sf::Time delta);
	void Animate(const std::string& target, int time, const std::string& easing = "linear");
	void Center(sf::Vector2f viewSize, bool x = true, bool y = true);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool IsDone() const;
private:
	bool center, centerX, centerY;
	sf::Vector2f viewSize;
	sf::Text text;
	std::string startText;
	std::string targetText;
	tweeny::tween<int> tween;
	bool done{};
};


#endif //GAMEPROTOTYPE_ANIMATEDTEXT_HPP
