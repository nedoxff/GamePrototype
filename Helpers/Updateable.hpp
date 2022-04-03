//
// Created by nedo on 03.04.2022.
//

#ifndef GAMEPROTOTYPE_UPDATEABLE_HPP
#define GAMEPROTOTYPE_UPDATEABLE_HPP
#include "../Core/Engine.hpp"

class Updateable
{
public:
	virtual void Update(sf::Time delta) = 0;
	virtual void ProcessEvent(Engine& engine, sf::Event& event) {}
};

#endif //GAMEPROTOTYPE_UPDATEABLE_HPP
