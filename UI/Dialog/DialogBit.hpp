//
// Created by nedo on 03.04.2022.
//

#ifndef GAMEPROTOTYPE_DIALOGBIT_HPP
#define GAMEPROTOTYPE_DIALOGBIT_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <optional>

struct DialogBit
{
	std::string Speaker;
	std::string Text;
	std::string TextureName;

	std::optional<sf::Texture> Texture;
};
#endif //GAMEPROTOTYPE_DIALOGBIT_HPP
