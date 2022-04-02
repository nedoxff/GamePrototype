//
// Created by nedo on 02.04.2022.
//

#ifndef GAMEPROTOTYPE_BUTTON_HPP
#define GAMEPROTOTYPE_BUTTON_HPP

#include "WindowComponent.hpp"
#include "../../Core/Engine.hpp"
#include "../Animation.hpp"

class Button: public WindowComponent {
public:
	Button(const Animation& animation, const sf::Vector2u& position = {});
	void ProcessEvent(Engine &engine, sf::Event &event) override;
	void Update(sf::Time delta) override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void SetEnabled(bool enabled);

protected:
	std::optional<const sf::Texture*> GetCurrentTexture() override;

private:
	Animation animation;
	bool clickable = true, enabled = true;
};


#endif //GAMEPROTOTYPE_BUTTON_HPP
