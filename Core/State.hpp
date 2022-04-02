//
// Created by nedo on 13.03.2022.
//

#ifndef GAMEPROTOTYPE_STATE_HPP
#define GAMEPROTOTYPE_STATE_HPP

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
class Engine;

class State: public sf::Drawable {
public:
	void Initialize(Engine* engine);
	virtual void Start() = 0;
	virtual void Update(sf::Time delta) = 0;
	virtual std::string GetName() = 0;
	virtual void ProcessEvent(Engine& engine, sf::Event& event) {}
protected:
	std::shared_ptr<ResourceManager> Resources;
	sf::Vector2f ViewSize;
	Engine* EnginePtr;
};


#endif //GAMEPROTOTYPE_STATE_HPP
