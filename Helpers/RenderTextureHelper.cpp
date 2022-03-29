//
// Created by nedo on 14.03.2022.
//

#include "RenderTextureHelper.hpp"
#include <cmath>

sf::Texture RenderTextureHelper::GenerateTextTexture(sf::Text text, int requiredWidth, int padding) {
	sf::RenderTexture renderTexture;
	sf::String startString = text.getString();
	while(static_cast<int>(std::ceil(text.getGlobalBounds().width)) < requiredWidth)
		text.setString(text.getString() + startString);

	renderTexture.create(requiredWidth + padding * 2, static_cast<int>(text.getLocalBounds().top + text.getLocalBounds().height) + padding * 2);
	renderTexture.clear(sf::Color::Transparent);
	renderTexture.draw(text);
	renderTexture.display();

	return {renderTexture.getTexture()};
}
