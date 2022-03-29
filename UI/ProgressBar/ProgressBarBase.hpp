//
// Created by nedo on 14.03.2022.
//

#ifndef GAMEPROTOTYPE_PROGRESSBARBASE_HPP
#define GAMEPROTOTYPE_PROGRESSBARBASE_HPP

#include "../../Helpers/Concepts.hpp"
#include <SFML/Graphics.hpp>


template<Integral T>
class ProgressBarBase: public sf::Drawable {
public:
	virtual void Increment(T by) = 0;
	virtual void Set(T value) = 0;

	virtual void SetMax(T max)
	{
		Max = max;
	}
	virtual void SetMin(T min)
	{
		Min = min;
	}

	virtual void SetTexture(const sf::Texture& texture) = 0;

	virtual sf::Vector2f GetPosition() = 0;

	virtual T MapNumber(T value, T inMin, T inMax, T outMin, T outMax)
	{
		return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
	}
protected:
	T Value = 0;
	T Min = 0;
	T Max = 100;
};


#endif //GAMEPROTOTYPE_PROGRESSBARBASE_HPP
