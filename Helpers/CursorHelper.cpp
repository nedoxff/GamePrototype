//
// Created by nedo on 22.03.2022.
//

#include "CursorHelper.hpp"
#include <utility>

CursorPack CursorHelper::cursorPack;

void CursorHelper::UseCursorPack(CursorPack& pack) {
	cursorPack = pack;
}

void CursorHelper::Set(Engine *engine, sf::Cursor::Type type) {
	engine->GetWindow()->setMouseCursor(*cursorPack.GetCursors()[type]);
}
