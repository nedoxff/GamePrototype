//
// Created by nedo on 14.03.2022.
//

#ifndef GAMEPROTOTYPE_OBJECTHELPER_HPP
#define GAMEPROTOTYPE_OBJECTHELPER_HPP

#include <SFML/Graphics.hpp>
#include "Concepts.hpp"

class ObjectHelper {
public:
	template<Transformable T>
	static void Center(T &obj, sf::Vector2f viewSize, bool centerX = true, bool centerY = true) {
		CenterOrigin(obj);
		if (centerX)
			obj.setPosition({viewSize.x / 2.f, obj.getPosition().y});
		if (centerY)
			obj.setPosition({obj.getPosition().x, viewSize.y / 2.f});
	}

	template<Transformable T, Transformable U>
	static void Center(T &obj, U &target, bool centerX = true, bool centerY = true) {
		CenterOrigin(obj);
		auto pos = target.getPosition();
		if (centerX)
			obj.setPosition({pos.x, obj.getPosition().y});
		if (centerY)
			obj.setPosition({obj.getPosition().x, pos.y});
	}

	template<Transformable T>
	static void CenterOrigin(T &shape) {
		auto bounds = shape.getLocalBounds();
		shape.setOrigin({bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f});
	}
};


#endif //GAMEPROTOTYPE_OBJECTHELPER_HPP
