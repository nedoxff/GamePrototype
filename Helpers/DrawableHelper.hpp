//
// Created by nedo on 20.03.2022.
//

#ifndef GAMEPROTOTYPE_DRAWABLEHELPER_HPP
#define GAMEPROTOTYPE_DRAWABLEHELPER_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class DrawableHelper {
public:
	static sf::Texture DrawWithShaders(const std::vector<sf::Drawable*>& objects, const std::vector<std::shared_ptr<sf::Shader>>& shaders, const sf::Vector2f& viewSize);
};


#endif //GAMEPROTOTYPE_DRAWABLEHELPER_HPP
