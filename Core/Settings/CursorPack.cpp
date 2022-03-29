//
// Created by nedo on 22.03.2022.
//

#include "CursorPack.hpp"
#include "../ResourceManager.hpp"
#include <pugixml.hpp>
using namespace pugi;

std::unordered_map<sf::Cursor::Type, std::string> CursorPack::CursorTypeToString = {
		{sf::Cursor::Arrow, "Arrow"},
		{sf::Cursor::ArrowWait, "ArrowWait"},
		{sf::Cursor::Wait, "Wait"},
		{sf::Cursor::Text, "Text"},
		{sf::Cursor::Hand, "Hand"},
		{sf::Cursor::SizeHorizontal, "SizeHorizontal"},
		{sf::Cursor::SizeVertical, "SizeVertical"},
		{sf::Cursor::SizeTopLeftBottomRight, "SizeTopLeftBottomRight"},
		{sf::Cursor::SizeBottomLeftTopRight, "SizeBottomLeftTopRight"},
		{sf::Cursor::SizeAll, "SizeAll"},
		{sf::Cursor::Cross, "Cross"},
		{sf::Cursor::Help, "Help"},
		{sf::Cursor::NotAllowed, "NotAllowed"}
};

void CursorPack::Load(ResourceManager *manager, const std::string &path) {
	xml_document document;
	xml_parse_result result = document.load_file(path.c_str());
	if(!result) {
		SPDLOG_ERROR("Failed to load cursor pack from \"{}\"!", path);
		std::abort();
	}

	SPDLOG_DEBUG("Loading cursor pack from \"{}\"", path);
	auto node = document.child("CursorPack");
	if(node.empty()) {
		SPDLOG_ERROR("Invalid cursor pack XML format! (missing CursorPack node)");
		std::abort();
	}

	auto name = std::string(node.attribute("Name").as_string());
	for(auto& child: node.children())
	{
		auto pair = std::find_if(CursorTypeToString.begin(), CursorTypeToString.end(), [&child](const std::pair<sf::Cursor::Type, std::string>& p){
			return p.second == std::string(child.name());
		});

		if(pair == CursorTypeToString.end()) {
			SPDLOG_WARN("Unknown cursor texture \"{}\"", child.name());
			continue;
		}

		auto x = child.attribute("HotspotX").as_int(0);
		auto y = child.attribute("HotspotY").as_int(0);
		auto texture = std::string(child.child_value());

		auto image = manager->GetTexture(texture).copyToImage();
		auto hotspot = sf::Vector2u(x, y);
		cursors[pair->first] = std::make_shared<sf::Cursor>();
		cursors[pair->first]->loadFromPixels(image.getPixelsPtr(), image.getSize(), hotspot);
		SPDLOG_DEBUG("Loaded cursor texture \"{}\" (hotspot: {}x{})", texture, x, y);
	}

	SPDLOG_INFO("Loaded cursor pack \"{}\" (from \"{}\")", name, path);
}

std::unordered_map<sf::Cursor::Type, std::shared_ptr<sf::Cursor>> &CursorPack::GetCursors() {
	return cursors;
}
