//
// Created by nedo on 12.03.2022.
//

#ifndef GAMEPROTOTYPE_ENGINE_HPP
#define GAMEPROTOTYPE_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "State.hpp"
#include "Logger.hpp"
#include "Settings/Config.hpp"
#include "../Helpers/Concepts.hpp"
#include <stack>

class Engine {
public:
	Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int style = sf::Style::Close);
	~Engine();


	template<Derived<State> T>
	void AddState(bool replacing = false)
	{
		auto ptr = std::make_unique<T>();
		AddState(ptr, replacing);
	}

	template<Derived<State> T>
	void AddState(std::unique_ptr<T>& ptr, bool replacing = false)
	{
		isAdding = true;
		isReplacing = replacing;
		pendingStates.push_back(std::move(ptr));
	}

	void PopState()
	{
		isDeleting = true;
	}

	void Start()
	{
		SPDLOG_INFO("Starting game loop");
		while(window->isOpen()) Tick();
	}

	std::unique_ptr<State>& GetActiveState()
	{
		return states.top();
	}

	void SetBackgroundColor(const sf::Color &backgroundColor);

	[[nodiscard]] const std::shared_ptr<ResourceManager> &GetResourceManager() const;
	[[nodiscard]] sf::Vector2f GetViewSize() const;

	Config &GetConfig();

	std::unique_ptr<sf::RenderWindow> &GetWindow();

private:
	void StateSwitched()
	{
		if(!states.empty())
		{
			SPDLOG_INFO("Switching state to {}", states.top()->GetName());
			states.top()->Initialize(this);
			states.top()->Start();
		}
		else SPDLOG_WARN("The state machine stack is empty!");
	}

	void ProcessStateMachine()
	{
		if(isDeleting && !states.empty()) {
			SPDLOG_DEBUG("Removing top state ({}) from the stack.", states.top()->GetName());
			states.pop();
			StateSwitched();
			isDeleting = false;
		}

		if(isAdding)
		{
			if(!states.empty())
			{
				if(isReplacing)
					states.pop();
			}
			for(auto& ptr: pendingStates) {
				SPDLOG_DEBUG("Adding state to the stack. Name: {} | Replacing: {}", ptr->GetName(), isReplacing ? "true": "false");
				states.push(std::move(ptr));
			}
			pendingStates.clear();
			StateSwitched();
			isAdding = false;
			isReplacing = false;
		}
	}

	Config config;
	bool isAdding = false, isReplacing = false, isDeleting = false;
	std::stack<std::unique_ptr<State>> states;
	std::vector<std::unique_ptr<State>> pendingStates;
	sf::Clock deltaClock;
	void Tick();
	sf::Color backgroundColor = sf::Color::Black;
	std::unique_ptr<sf::RenderWindow> window;
	std::shared_ptr<ResourceManager> resourceManager;
};


#endif //GAMEPROTOTYPE_ENGINE_HPP
