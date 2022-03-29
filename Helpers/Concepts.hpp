//
// Created by nedo on 16.03.2022.
//

#ifndef GAMEPROTOTYPE_CONCEPTS_HPP
#define GAMEPROTOTYPE_CONCEPTS_HPP

#include <type_traits>

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

template<class T>
concept Transformable = std::is_base_of<sf::Shape, T>::value or std::is_same<sf::Text, T>::value;

template<class T>
concept Integral = std::is_integral<T>::value;

#endif //GAMEPROTOTYPE_CONCEPTS_HPP
