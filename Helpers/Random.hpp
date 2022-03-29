//
// Created by nedo on 16.03.2022.
//

#ifndef GAMEPROTOTYPE_RANDOM_HPP
#define GAMEPROTOTYPE_RANDOM_HPP

#include "Concepts.hpp"
#include <random>
class Random {
public:
	template<Integral T>
	static T Next(T from, T to)
	{
		std::random_device r;
		std::mt19937 dre(r());
		std::uniform_int_distribution<T> dist(from, to);
		return dist(dre);
	}

	static bool NextBool()
	{
		std::random_device r;
		std::mt19937 dre(r());
		std::bernoulli_distribution dist(0.5);
		return dist(dre);
	}

	template<class T>
	static const T& NextFromVector(const std::vector<T>& vec)
	{
		return vec[Next<int>(0, vec.size() - 1)];
	}
};


#endif //GAMEPROTOTYPE_RANDOM_HPP
