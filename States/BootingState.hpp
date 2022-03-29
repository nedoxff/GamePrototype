//
// Created by nedo on 18.03.2022.
//

#ifndef GAMEPROTOTYPE_BOOTINGSTATE_HPP
#define GAMEPROTOTYPE_BOOTINGSTATE_HPP

#include "../Core/State.hpp"
#include "../Helpers/Scheduler.hpp"
#include <tweeny.h>
#include <Motion/Motion.hpp>

class BootingState: public State {
public:
	void Start() override;

	void Update(sf::Time delta) override;

	std::string GetName() override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	Scheduler scheduler;
	tweeny::tween<int> tween;

	sf::RectangleShape screen;
	sf::Texture screenTexture;
	sf::Text titleText;

	std::unique_ptr<mt::SFMLVideoPlayback> videoPlayback;
	[[maybe_unused]] std::unique_ptr<mt::SFMLAudioPlayback> audioPlayback;
	std::shared_ptr<sf::Shader> fishEyeShader;
	std::shared_ptr<mt::DataSource> bootSource;

	bool tweenUpdate = false;
};


#endif //GAMEPROTOTYPE_BOOTINGSTATE_HPP
