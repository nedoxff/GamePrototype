//
// Created by nedo on 25.03.2022.
//

#include "Animation.hpp"
#include "../Core/Logger.hpp"
#include <pugixml.hpp>
using namespace pugi;

void Animation::Load(const std::shared_ptr<ResourceManager>& manager, const std::string& path) {

	xml_document document;
	xml_parse_result result = document.load_file(path.c_str());
	if(!result)
		throw std::runtime_error("Failed to load animation information from \"" + path + "\"!");

	auto root = document.child("Animation");
	auto mode = std::string(root.attribute("Mode").as_string("Rectangle"));

	if(mode == "Rectangle")
	{
		auto sizeX = root.attribute("SizeX").as_int(-1);
		auto sizeY = root.attribute("SizeY").as_int(-1);
		if(sizeX == -1 || sizeY == -1)
		{
			shape = std::make_unique<sf::RectangleShape>();
			SPDLOG_WARN("SizeX or SizeY not specified for \"Rectangle\" mode, defaulting to texture size.");
			useTextureSize = true;
		}
		else
			shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(static_cast<float>(sizeX), static_cast<float>(sizeY)));
	}
	else
		throw std::runtime_error("Invalid \"Mode\" attribute specified");

	loop = root.attribute("Loop").as_bool(false);

	for(auto& node: root.children())
	{
		auto childName = std::string(node.name());
		if(childName != "Frame")
			throw std::runtime_error("Unexpected child node \"" + childName + "\" in animation information");

		if(!node.attribute("Duration"))
			throw std::runtime_error("Expected \"Duration\" attribute in Frame node");

		Frame frame;

		frame.Duration = node.attribute("Duration").as_int();
		if(!node.attribute("Texture").empty())
			frame.Texture = manager->GetTexture(node.attribute("Texture").as_string());

		frames.push_back(frame);
	}
}

void Animation::Update(sf::Time delta) {
	if(!playing) return;
	if(frames.empty())
	{
		playing = false;
		return;
	}

	currentDelta += delta.asMilliseconds();
	if(frames[frameIndex].Duration <= currentDelta)
	{
		currentDelta = 0;
		if(frameIndex + 1 < frames.size())
			frameIndex++;
		else {
			playing = loop;
			if(loop) frameIndex = 0;
		}
		SetFrame(frameIndex);
	}
}

void Animation::SetLoop(bool loop) {
	this->loop = loop;
}

void Animation::Play() {
	playing = true;
	if(frameIndex == frames.size() - 1) frameIndex = 0;
	SetFrame(frameIndex);
}

void Animation::SetFrame(int index) {
	if(frameIndex != index) frameIndex = index;
	if(frames[index].Texture.has_value()) {
		shape->setTexture(&frames[index].Texture.value());
		if(useTextureSize)
		{
			auto rectangle = std::static_pointer_cast<sf::RectangleShape>(shape);
			rectangle->setSize(static_cast<sf::Vector2f>(rectangle->getTexture()->getSize()));
		}
	}
}

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if(shape)
		target.draw(*shape);
}

bool Animation::IsPlaying() const {
	return playing;
}

bool Animation::IsLoop() const {
	return loop;
}

void Animation::Pause() {
	playing = false;
}

std::shared_ptr<sf::Shape> &Animation::GetShape() {
	return shape;
}
