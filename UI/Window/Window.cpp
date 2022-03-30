//
// Created by nedo on 28.03.2022.
//

#include "Window.hpp"
#include <pugixml.hpp>
#include "../../Core/Logger.hpp"
using namespace pugi;

void Window::Load(const std::string &path) {
	xml_document document;
	xml_parse_result result = document.load_file(path.c_str());
	if(!result)
		throw std::runtime_error(fmt::format("Failed to load window information from \"{}\"!", path));

	auto root = document.child("Window");

	auto base = root.child("Base");
	if(base.empty())
		throw std::runtime_error("Window must have a Base element!");

	auto sizeX = base.attribute("SizeX").as_int(-1);
	auto sizeY = base.attribute("SizeY").as_int(-1);
	auto textureNode = base.attribute("Texture");

	if(sizeX == -1 || sizeY == -1)
	{
		if(textureNode.empty())
			throw std::runtime_error("One of properties (SizeX or SizeY) was not specified and there is no texture to fallback!");
		else
			SPDLOG_WARN("One of properties (SizeX or SizeY) was not specified. Using texture size instead.");
	}
}
