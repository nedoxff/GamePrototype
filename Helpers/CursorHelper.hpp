//
// Created by nedo on 22.03.2022.
//

#ifndef GAMEPROTOTYPE_CURSORHELPER_HPP
#define GAMEPROTOTYPE_CURSORHELPER_HPP

#include <unordered_map>
#include <SFML/Window.hpp>
#include "../Core/Engine.hpp"
#include "../Core/Settings/CursorPack.hpp"
class CursorHelper {
public:
	static void UseCursorPack(CursorPack& pack);
	static void Set(Engine* engine, sf::Cursor::Type type);
private:
	static CursorPack cursorPack;
};


#endif //GAMEPROTOTYPE_CURSORHELPER_HPP
