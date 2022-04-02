//
// Created by nedo on 22.03.2022.
//

#ifndef GAMEPROTOTYPE_CURSORPACK_HPP
#define GAMEPROTOTYPE_CURSORPACK_HPP


#include <map>
#include <memory>
#include <SFML/Window.hpp>
#include <iostream>
#include <unordered_map>

class ResourceManager;
class CursorPack {
public:
	CursorPack() = default;
	static std::unordered_map<sf::Cursor::Type, std::string> CursorTypeToString;

	void Load(ResourceManager* manager, const std::string& path);
	std::unordered_map<sf::Cursor::Type, std::shared_ptr<sf::Cursor>> &GetCursors();
private:
	std::unordered_map<sf::Cursor::Type, std::shared_ptr<sf::Cursor>> cursors;
};


#endif //GAMEPROTOTYPE_CURSORPACK_HPP
