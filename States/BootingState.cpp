//
// Created by nedo on 18.03.2022.
//

#include "BootingState.hpp"
#include "../Helpers/ObjectHelper.hpp"
#include "../Helpers/DrawableHelper.hpp"
#include "../Core/Engine.hpp"

#define FIRST_EVENT 2333
#define SECOND_EVENT 10333
#define THIRD_EVENT 15400

void BootingState::Start() {
	screen.setSize({1280, 720});

	bootSource = Resources->GetVideo("Boot");

	fishEyeShader = Resources->GetShader("FishEye", "BarrelFishEyeF", "Default");
	fishEyeShader->setUniform("texture", sf::Shader::CurrentTexture);
	fishEyeShader->setUniform("power", 1.1f);

	videoPlayback = std::make_unique<mt::SFMLVideoPlayback>(*bootSource);
	auto size = bootSource->GetVideoSize();
	videoPlayback->setScale(ViewSize.x / size.x, ViewSize.y / size.y);

	audioPlayback = std::make_unique<mt::SFMLAudioPlayback>(*bootSource);

	titleText.setFont(Resources->GetFont("dos"));
	titleText.setCharacterSize(72);
	titleText.setOutlineColor({0, 0, 0, 0});
	titleText.setFillColor({255, 255, 255, 0});
	titleText.setOutlineThickness(5.f);
	titleText.setString("_ned0programmer");
	ObjectHelper::Center(titleText, ViewSize);

	bootSource->Play();

	scheduler.Schedule(sf::milliseconds(FIRST_EVENT), [this](){
		tweenUpdate = true;
		titleText.setString("_ned0programmer");
		tween = tweeny::from(0).to(255).during(2500);
		tween.onStep([this](int v){
			titleText.setFillColor({255, 255, 255, static_cast<unsigned char>(v)});
			titleText.setOutlineColor({0, 0, 0, static_cast<unsigned char>(v)});
			if(v == 255)
			{
				tweenUpdate = false;
				return true;
			}
			return false;
		});
	});

	scheduler.Schedule(sf::milliseconds(SECOND_EVENT), [this](){
		titleText.setString("some random quote");
		ObjectHelper::Center(titleText, ViewSize);
	});

	scheduler.Schedule(sf::milliseconds(THIRD_EVENT), [this](){
		tweenUpdate = true;
		tween = tweeny::from(255).to(0).during(5000);
		tween.onStep([this](int v){
			titleText.setFillColor({255, 255, 255, static_cast<unsigned char>(v)});
			titleText.setOutlineColor({0, 0, 0, static_cast<unsigned char>(v)});
			if(v == 0)
			{
				tweenUpdate = false;
				return true;
			}
			return false;
		});
	});
}

void BootingState::Update(sf::Time delta) {
	scheduler.Update(delta);
	bootSource->Update();
	if(tweenUpdate)
		tween.step(delta.asMilliseconds());

	screenTexture = DrawableHelper::DrawWithShaders({&*videoPlayback}, {fishEyeShader}, ViewSize);
	screen.setTexture(&screenTexture);

	if(bootSource->IsEndofFileReached())
	{
		EnginePtr->GetConfig().SetFirstLaunch(false);
		EnginePtr->GetConfig().Save();
		EnginePtr->PopState();
	}
}

std::string BootingState::GetName() {
	return "Booting State";
}

void BootingState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(screen);
	target.draw(titleText);
}
