//
// Created by nedo on 03.04.2022.
//

#include "Dialog.hpp"

#include <pugixml.hpp>
using namespace pugi;

#include "../../Helpers/ObjectHelper.hpp"

#define X_OFFSET 20
#define Y_OFFSET 20
#define HEIGHT_FACTOR 3.5f

void Dialog::Load(const std::shared_ptr<ResourceManager>& manager, const std::string& path) {
	xml_document document;
	xml_parse_result result = document.load_file(path.c_str());
	if(!result)
		throw std::runtime_error(fmt::format("Failed to load dialog information from \"{}\"!", path));

	auto root = document.child("Dialog");
	if(root.empty())
		throw std::runtime_error("Dialog information must have a \"Dialog\" object as root!");

	animationSpeed = root.attribute("AnimationSpeed").as_float(1.5f);

	for(auto& child: root.children())
	{
		auto childName = std::string(child.name());
		if(childName != "Bit")
			throw std::runtime_error("Dialog object must only have \"Bit\" objects as children!");

		DialogBit bit;

		if(!child.text())
			throw std::runtime_error("Bit object must have the text as node value!");
		bit.Text = child.text().get();

		auto speakerNode = child.attribute("Speaker");
		if(speakerNode.empty())
			throw std::runtime_error("Bit object must have a \"Speaker\" attribute!");
		bit.Speaker = speakerNode.as_string();

		auto textureNode = child.attribute("Texture");
		if(textureNode.empty()) {
			bit.Texture = std::nullopt;
			bit.TextureName = "";
		}
		else
		{
			bit.TextureName = textureNode.as_string();
			bit.Texture = manager->GetTexture(bit.TextureName);
		}

		bits.push_back(bit);
	}
	loaded = true;
}

void Dialog::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if(!loaded) return;

	target.draw(mainBox);
}

bool Dialog::IsPlaying() const {
	return playing;
}

void Dialog::Play() {
	if(!loaded) return;

	if(bits.empty())
	{
		SPDLOG_WARN("Cannot play an empty dialog. Ignoring");
		return;
	}

	if(playing)
	{
		SPDLOG_WARN("Cannot play a dialog that already started. Ignoring");
		return;
	}

	playing = true;
	state = AnimationStart;

	scaleTween = tweeny::from(0.f, 0.f).to(1.f, 1.f).via(tweeny::easing::quadraticInOut).during(static_cast<int>(750 * animationSpeed), static_cast<int>(750 * (animationSpeed - 0.2f)));
	scaleTween.onStep([this](float h, float v){
		mainBox.setScale({h, v});
		return h == 1.f && v == 1.f;
	});
}

Dialog::Dialog(sf::Vector2f viewSize) {
	mainBox.setSize({viewSize.x - X_OFFSET * 2, viewSize.y / HEIGHT_FACTOR});
	mainBox.setFillColor(sf::Color::Black);
	mainBox.setOutlineThickness(3.f);
	mainBox.setOutlineColor(sf::Color::White);
	mainBox.setCornersRadius(5.f);
	mainBox.setCornerPointCount(30);

	ObjectHelper::CenterOrigin(mainBox);

	auto bounds = mainBox.getGlobalBounds();
	mainBox.setPosition({X_OFFSET + bounds.width / 2.f, viewSize.y - bounds.height / 2.f - Y_OFFSET});
	mainBox.setScale({0, 0});
}

void Dialog::Pause() {
	playing = false;
}

void Dialog::Update(sf::Time delta) {
	if(!loaded) return;
	switch(state)
	{
		case Idle:
			break;
		case AnimationStart: {
			scaleTween.step(delta.asMilliseconds());
			break;
		}
		case TypingText:
			break;
		case WaitingForInput:
			break;
		case AnimationEnd:
			break;
	}
}
