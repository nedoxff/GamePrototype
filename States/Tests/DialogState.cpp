//
// Created by nedo on 03.04.2022.
//

#include "DialogState.hpp"

using namespace ImGui;

void DialogState::Start() {
	dialog = Dialog(ViewSize);
}

void DialogState::Update(sf::Time delta) {
	if(dialog.IsPlaying())
		dialog.Update(delta);

	Begin("Dialog UI Debug Window");

	InputText("Document Name", &documentName);
	if(Button("Load"))
	{
		loaded = false;
		try {
			dialog.Load(Resources, Resources->GetDocument(documentName));
			info = "Loaded successfully!";
			infoColor = {0, 1, 0, 1};
			loaded = true;
		}
		catch(std::runtime_error& err)
		{
			SPDLOG_ERROR("Failed to load dialog information for DialogState: {}", err.what());
			info = "Failed to load dialog UI: " + std::string(err.what());
			infoColor = {1, 0, 0, 1};
		}
	}

	PushTextWrapPos();
	TextColored(infoColor, "%s", info.c_str());
	PopTextWrapPos();

	Separator();

	if(loaded)
	{
		if(TreeNode("Controls")) {
			BeginDisabled(dialog.IsPlaying());
			if (Button("Play"))
				dialog.Play();
			EndDisabled();

			SameLine();

			BeginDisabled(!dialog.IsPlaying());
			if(Button("Pause"))
				dialog.Pause();
			EndDisabled();

			TreePop();
		}

	}

	End();
}

std::string DialogState::GetName() {
	return "[Debug] Dialog UI State";
}

void DialogState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(dialog);
}
