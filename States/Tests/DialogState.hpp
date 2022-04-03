//
// Created by nedo on 03.04.2022.
//

#ifndef GAMEPROTOTYPE_DIALOGSTATE_HPP
#define GAMEPROTOTYPE_DIALOGSTATE_HPP

#include "../../Core/State.hpp"
#include "../../UI/Dialog/Dialog.hpp"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui-SFML.h>
class DialogState: public State {
public:
	void Start() override;
	void Update(sf::Time delta) override;
	std::string GetName() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	std::string documentName;
	std::string info;
	ImVec4 infoColor = {1, 1, 1, 1};
	bool loaded = false;

	Dialog dialog;
};


#endif //GAMEPROTOTYPE_DIALOGSTATE_HPP
