//
// Created by nedo on 21.03.2022.
//

#ifndef GAMEPROTOTYPE_MENUSTATE_HPP
#define GAMEPROTOTYPE_MENUSTATE_HPP

#include "../Core/State.hpp"
#include "../UI/Fade.hpp"

class MenuState: public State {
public:
	void Start() override;
	void Update(sf::Time delta) override;
	std::string GetName() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	sf::RectangleShape screen;
	sf::Texture screenTexture;
	std::shared_ptr<sf::Shader> fishEyeShader;

	sf::RectangleShape background;
	Fade fade;
};


#endif //GAMEPROTOTYPE_MENUSTATE_HPP
