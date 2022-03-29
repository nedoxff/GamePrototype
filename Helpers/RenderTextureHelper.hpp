//
// Created by nedo on 14.03.2022.
//

#ifndef GAMEPROTOTYPE_RENDERTEXTUREHELPER_HPP
#define GAMEPROTOTYPE_RENDERTEXTUREHELPER_HPP

#include <SFML/Graphics.hpp>

class RenderTextureHelper {
public:
	static sf::Texture GenerateTextTexture(sf::Text text, int requiredWidth, int padding = 5);
};


#endif //GAMEPROTOTYPE_RENDERTEXTUREHELPER_HPP
