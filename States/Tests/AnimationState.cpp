//
// Created by nedo on 25.03.2022.
//

#include "AnimationState.hpp"
using namespace ImGui;

void AnimationState::Start() {

}

void AnimationState::Update(sf::Time delta) {
	animation.Update(delta);

	Begin("Animation Debug Window");

	InputText("Document Name", &documentName);
	if(Button("Load"))
	{
		loaded = false;
		try {
			animation = Animation();
			animation.Load(Resources, Resources->GetDocument(documentName));
			info = "Loaded successfully!";
			infoColor = {0, 1, 0, 1};
			loaded = true;

			selectedFrame = 1;
			loop = animation.IsLoop();
		}
		catch(std::runtime_error& err)
		{
			SPDLOG_ERROR("Failed to load animation for AnimationState: {}", err.what());
			info = "Failed to load animation: " + std::string(err.what());
			infoColor = {1, 0, 0, 1};
		}
	}

	PushTextWrapPos();
	TextColored(infoColor, "%s", info.c_str());
	PopTextWrapPos();

	Separator();

	if(loaded)
	{
		if(animation.IsPlaying())
			selectedFrame = animation.frameIndex + 1;
		auto& texture = animation.frames[animation.frameIndex].Texture;
		if(texture)
			Image(sf::Sprite(texture.value()));
		SameLine();
		if(Button("Play"))
			animation.Play();
		SameLine();
		if(Button("Pause"))
			animation.Pause();

		if(Checkbox("Loop", &loop))
			animation.SetLoop(loop);

		if(SliderInt("Frame No.", &selectedFrame, 1, animation.frames.size()))
			animation.SetFrame(selectedFrame - 1);

		Separator();

		Text("Frame Duration: %d", animation.frames[animation.frameIndex].Duration);

		std::ostringstream ss;
		ss << & animation.frames[animation.frameIndex].Texture.value();

		Text("Texture Address: %s", ss.str().c_str());
	}

	End();
}

std::string AnimationState::GetName() {
	return "[Testing] Animation State";
}

void AnimationState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(animation);
}
