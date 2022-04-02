//
// Created by nedo on 02.04.2022.
//

#ifndef GAMEPROTOTYPE_WINDOWCOMPONENT_HPP
#define GAMEPROTOTYPE_WINDOWCOMPONENT_HPP

#include <SFML/Graphics.hpp>

#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <optional>
#include "../../Core/Engine.hpp"

class WindowState;

class WindowComponent: public sf::Drawable {
public:
	virtual void ProcessEvent(Engine &engine, sf::Event &event) = 0;
	virtual void Update(sf::Time delta) = 0;
protected:
	friend class WindowState;

	virtual std::optional<const sf::Texture*> GetCurrentTexture() {return std::nullopt;}
	std::unordered_set<std::string> RequiredCallbacks;
	std::unordered_map<std::string, std::function<void()>> Callbacks;
};


#endif //GAMEPROTOTYPE_WINDOWCOMPONENT_HPP
