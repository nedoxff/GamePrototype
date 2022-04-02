//
// Created by nedo on 28.03.2022.
//

#ifndef GAMEPROTOTYPE_WINDOW_HPP
#define GAMEPROTOTYPE_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "WindowComponent.hpp"
#include "../../Core/Engine.hpp"

enum WindowComponentType
{
	ButtonComponent
};

class WindowState;

class Window: public sf::Drawable {
public:
	Window() = default;
	void Load(std::shared_ptr<ResourceManager>& manager, const std::string& path);
	void ProcessEvent(Engine& engine, sf::Event& event);
	void Update(sf::Time delta);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	friend class WindowState;

	bool loaded = false;
	static std::unordered_map<std::string, WindowComponentType> stringConverter;
	sf::RectangleShape base;
	std::unordered_map<std::string, std::unique_ptr<WindowComponent>> components;
};


#endif //GAMEPROTOTYPE_WINDOW_HPP
