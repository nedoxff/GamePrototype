//
// Created by nedo on 14.03.2022.
//

#ifndef GAMEPROTOTYPE_VERTICALPROGRESSBAR_HPP
#define GAMEPROTOTYPE_VERTICALPROGRESSBAR_HPP

#include "ProgressBarBase.hpp"

template<Integral T>
class VerticalProgressBar: public ProgressBarBase<T>
{
public:
	VerticalProgressBar() = default;
	VerticalProgressBar(sf::Vector2f position, sf::Vector2f size, sf::Color innerColor, sf::Color outerColor, float outerOutlineThickness = 5)
	{
		outer.setSize(size);
		outer.setPosition(position);
		outer.setOutlineColor(outerColor);
		outer.setOutlineThickness(outerOutlineThickness);
		outer.setFillColor(sf::Color::Transparent);

		maxSize = {size.x, size.y};
		inner.setSize(maxSize);
		inner.setPosition({position.x, position.y});
		inner.setFillColor(innerColor);
	}

	void SetReversed(bool reversed) {
		this->reversed = reversed;
	}

	void Increment(T by) override {
		if(this->Value + by > this->Max) this->Value = this->Max;
		else this->Value += by;
		inner.setSize({maxSize.x, static_cast<float>(this->MapNumber(this->Value, this->Min, this->Max, 0, maxSize.y))});
		if(inner.getTexture() != nullptr)
			inner.setTextureRect({0, 0, static_cast<int>(inner.getTexture()->getSize().x), static_cast<int>(inner.getSize().y)});
		if(reversed)
			inner.setPosition({inner.getPosition().x, outer.getPosition().y + outer.getGlobalBounds().height - inner.getGlobalBounds().height - outer.getOutlineThickness() * 2});
	}

	void SetTexture(const sf::Texture& texture) override {
		textureCopy = sf::Texture(texture);
		textureCopy.setRepeated(true);
		inner.setTexture(&textureCopy);
		inner.setTextureRect({0, 0, static_cast<int>(textureCopy.getSize().x), static_cast<int>(textureCopy.getSize().y)});
	}

	void Set(T value) override {
		if(value > this->Max) this->Value = this->Max;
		else this->Value = value;
		inner.setSize({maxSize.x, static_cast<float>(this->MapNumber(this->Value, this->Min, this->Max, 0, maxSize.y))});
		if(inner.getTexture() != nullptr)
			inner.setTextureRect({0, 0, static_cast<int>(inner.getTexture()->getSize().x), static_cast<int>(inner.getSize().y)});
		if(reversed)
			inner.setPosition({inner.getPosition().x, outer.getPosition().y + outer.getGlobalBounds().height - inner.getGlobalBounds().height - outer.getOutlineThickness() * 2});
	}

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
		target.draw(outer);
		target.draw(inner);
	}

	sf::Vector2f GetPosition() override
	{
		return outer.getPosition();
	}

private:
	bool reversed = false;
	sf::RectangleShape inner;
	sf::RectangleShape outer;
	sf::Vector2f maxSize;
	sf::Texture textureCopy;
};
#endif //GAMEPROTOTYPE_VERTICALPROGRESSBAR_HPP
