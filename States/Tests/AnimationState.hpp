//
// Created by nedo on 25.03.2022.
//

#ifndef GAMEPROTOTYPE_ANIMATIONSTATE_HPP
#define GAMEPROTOTYPE_ANIMATIONSTATE_HPP

#include "../../Core/State.hpp"
#include "../../UI/Animation.hpp"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui-SFML.h>

class AnimationState: public State {
public:
	void Start() override;
	void Update(sf::Time delta) override;
	std::string GetName() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	Animation animation;
	std::string documentName;
	std::string info;
	ImVec4 infoColor = {1, 1, 1, 1};
	bool loaded = false;
	int selectedFrame;
	bool loop;
};


#endif //GAMEPROTOTYPE_ANIMATIONSTATE_HPP
