//
// Created by nedo on 28.03.2022.
//

#include "Window.hpp"
#include <pugixml.hpp>
#include "../../Core/Logger.hpp"
#include "Button.hpp"
using namespace pugi;

std::unordered_map<std::string, WindowComponentType> Window::stringConverter = {
		{"Button", ButtonComponent}
};

void Window::Load(std::shared_ptr<ResourceManager>& manager, const std::string& path) {
	loaded = false;
	xml_document document;
	xml_parse_result result = document.load_file(path.c_str());
	if(!result)
		throw std::runtime_error(fmt::format("Failed to load window information from \"{}\"!", path));

	auto root = document.child("Window");

	auto baseNode = root.child("Base");
	if(baseNode.empty())
		throw std::runtime_error("Window must have a Base element!");
	auto textureNode = baseNode.attribute("Texture");
	if(textureNode.empty())
		throw std::runtime_error("Base must have a Texture attribute!");

	base.setTexture(&manager->GetTexture(textureNode.value()));

	auto sizeX = baseNode.attribute("SizeX").as_float(-1);
	auto sizeY = baseNode.attribute("SizeY").as_float(-1);

	if(sizeX == -1 || sizeY == -1)
	{
		SPDLOG_WARN("One of properties (SizeX or SizeY) was not specified. Using texture size instead.");
		base.setSize(static_cast<sf::Vector2f>(base.getTexture()->getSize()));
	}
	else
		base.setSize({sizeX, sizeY});

	for(auto& child: root)
	{
		auto childName = std::string(child.name());
		if(childName == "Base") continue;

		auto idNode = child.attribute("Id");
		if(child.attribute("Id").empty())
			throw std::runtime_error("A window component must have an Id attribute!");
		auto id = idNode.value();

		auto x = child.attribute("X").as_int(0);
		auto y = child.attribute("Y").as_int(0);

		switch(stringConverter[childName])
		{
			case ButtonComponent:
			{
				auto animationNode = child.attribute("Animation");
				if(animationNode.empty())
					throw std::runtime_error("Button window component must have an Animation attribute!");
				auto animationName = std::string(animationNode.value());

				try
				{
					auto animation = Animation();
					animation.Load(manager, manager->GetDocument(animationName));

					components[id] = std::make_unique<Button>(animation, sf::Vector2u(x, y));
					SPDLOG_DEBUG("Created a button window component with ID \"{}\".", id);
				}
				catch(const std::runtime_error& err) {
					throw std::runtime_error(
							fmt::format("Failed to load animation \"{}\" for a button component. Reason: {}",
							            animationName, err.what()));
				}
				break;
			}
			default:
				SPDLOG_WARN("Unknown window component \"{}\". Skipping");
				break;
		}
	}
	loaded = true;
}

void Window::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if(!loaded) return;
	target.draw(base);
	for(auto& [id, component]: components)
		target.draw(*component);
}

void Window::ProcessEvent(Engine &engine, sf::Event &event) {
	for(auto& [id, component]: components)
		component->ProcessEvent(engine, event);
}

void Window::Update(sf::Time delta) {
	for(auto& [id, component]: components)
		component->Update(delta);
}
