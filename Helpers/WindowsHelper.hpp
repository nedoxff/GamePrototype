//
// Created by nedo on 24.03.2022.
//

#ifndef GAMEPROTOTYPE_WINDOWSHELPER_HPP
#define GAMEPROTOTYPE_WINDOWSHELPER_HPP

#include <SFML/Graphics.hpp>

class WindowsHelper {
public:
	static void OnStartup();
	static void OnShutdown();

	static std::pair<sf::Vector2i, sf::Vector2i> GetPrimaryMonitorSize();
	static void ShowTaskBar(bool show);
};


#endif //GAMEPROTOTYPE_WINDOWSHELPER_HPP
