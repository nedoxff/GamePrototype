//
// Created by nedo on 28.03.2022.
//

#ifndef GAMEPROTOTYPE_WINDOW_HPP
#define GAMEPROTOTYPE_WINDOW_HPP

#include <SFML/Graphics.hpp>

class Window: public sf::Drawable {
public:
	Window() = default;
	void Load(const std::string& path);
private:

};


#endif //GAMEPROTOTYPE_WINDOW_HPP
