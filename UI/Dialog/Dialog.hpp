//
// Created by nedo on 03.04.2022.
//

#ifndef GAMEPROTOTYPE_DIALOG_HPP
#define GAMEPROTOTYPE_DIALOG_HPP

#include <SFML/Graphics.hpp>
#include "../../Core/ResourceManager.hpp"
#include "../../Extensions/RoundedRectangleShape.hpp"
#include "DialogBit.hpp"
#include <tweeny.h>

class Dialog: public sf::Drawable {
public:
	explicit Dialog(sf::Vector2f viewSize);
	Dialog() = default;
	void Load(const std::shared_ptr<ResourceManager>& manager, const std::string& path);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool IsPlaying() const;
	void Pause();
	void Play();

private:
	enum DialogState
	{
		Idle,
		AnimationStart,
		TypingText,
		WaitingForInput,
		AnimationEnd
	};

	std::vector<DialogBit> bits;
	bool playing = false;
	bool loaded = false;
	DialogState state = Idle;

	float animationSpeed;

	tweeny::tween<float> scaleTween;
	sf::RoundedRectangleShape mainBox;
	sf::RoundedRectangleShape speakerBox;
	sf::RectangleShape speaker;
};


#endif //GAMEPROTOTYPE_DIALOG_HPP
