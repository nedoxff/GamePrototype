//
// Created by nedo on 13.03.2022.
//

#ifndef GAMEPROTOTYPE_STATE_HPP
#define GAMEPROTOTYPE_STATE_HPP

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "../Helpers/Updateable.hpp"
class Engine;

class State: public sf::Drawable, public Updateable {
public:
	void Initialize(Engine* engine);
	virtual void Start() = 0;
	virtual std::string GetName() = 0;
protected:
	std::shared_ptr<ResourceManager> Resources;
	sf::Vector2f ViewSize;
	Engine* EnginePtr;
};


#endif //GAMEPROTOTYPE_STATE_HPP
