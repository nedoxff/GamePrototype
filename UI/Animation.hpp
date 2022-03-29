//
// Created by nedo on 25.03.2022.
//

#ifndef GAMEPROTOTYPE_ANIMATION_HPP
#define GAMEPROTOTYPE_ANIMATION_HPP


#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include "../Core/ResourceManager.hpp"

struct Frame // NOLINT(cppcoreguidelines-pro-type-member-init)
{
	int Duration;
	std::optional<sf::Texture> Texture = std::nullopt;
};

class AnimationState;

class Animation: public sf::Drawable {
public:
	Animation() = default;
	void Load(const std::shared_ptr<ResourceManager>& manager, const std::string& path);
	void Update(sf::Time delta);
	void Play();
	void Pause();

	void SetLoop(bool loop);
	void SetFrame(int index);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	[[nodiscard]] bool IsPlaying() const;

	[[nodiscard]] bool IsLoop() const;

private:

	friend class AnimationState;

	int frameIndex = 0;
	int currentDelta = 0;

	bool loop = false;
	bool useTextureSize = false;
	bool playing = false;

	std::shared_ptr<sf::Shape> shape;
	std::vector<Frame> frames;
};


#endif //GAMEPROTOTYPE_ANIMATION_HPP
