//
// Created by nedo on 03.04.2022.
//

#ifndef GAMEPROTOTYPE_DEBUGSTATE_HPP
#define GAMEPROTOTYPE_DEBUGSTATE_HPP

#include "../../Core/State.hpp"
class DebugState: public State {
public:
	void Start() override;
	void Update(sf::Time delta) override;
	std::string GetName() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Text text;
};


#endif //GAMEPROTOTYPE_DEBUGSTATE_HPP
