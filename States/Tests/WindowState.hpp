//
// Created by nedo on 03.04.2022.
//

#ifndef GAMEPROTOTYPE_WINDOWSTATE_HPP
#define GAMEPROTOTYPE_WINDOWSTATE_HPP

#include "../../Core/State.hpp"
#include "../../UI/Window/Window.hpp"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui-SFML.h>

class WindowState: public State {
public:
	void Start() override;
	void Update(sf::Time delta) override;
	std::string GetName() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void ProcessEvent(Engine &engine, sf::Event &event) override;
private:
	Window window;

	std::string documentName;
	std::string info;
	ImVec4 infoColor = {1, 1, 1, 1};
	bool loaded = false;
};


#endif //GAMEPROTOTYPE_WINDOWSTATE_HPP
