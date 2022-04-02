//
// Created by nedo on 03.04.2022.
//

#include "WindowState.hpp"
using namespace ImGui;

void WindowState::Start() {
	window = Window();
}

void WindowState::Update(sf::Time delta) {
	window.Update(delta);

	Begin("Window UI Debug Window");

	InputText("Document Name", &documentName);
	if(Button("Load"))
	{
		loaded = false;
		try {
			window.Load(Resources, Resources->GetDocument(documentName));
			info = "Loaded successfully!";
			infoColor = {0, 1, 0, 1};
			loaded = true;
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
		if(TreeNode("Base"))
		{
			Text("Texture (current): %fx%f", window.base.getSize().x, window.base.getSize().y);
			Image(*window.base.getTexture());
			TreePop();
		}
		if(TreeNode("Components"))
		{
			for(auto& [id, component]: window.components)
			{
				if(TreeNode(id.c_str()))
				{
					if(component->GetCurrentTexture()) {
						auto texture = component->GetCurrentTexture().value();
						Text("Texture (current): %ux%u", texture->getSize().x, texture->getSize().y);
						Image(*texture);
					}
					for(auto& requiredCallback: component->RequiredCallbacks)
					{
						Text("%s: ", requiredCallback.c_str());
						SameLine();
						if(component->Callbacks[requiredCallback]) {
							if (Button("Invoke"))
								component->Callbacks[requiredCallback]();
						}
						else
							Text("*not implemented*");
					}
					TreePop();
				}
			}
			TreePop();
		}
	}

	End();
}

std::string WindowState::GetName() {
	return "[Testing] Window UI State";
}

void WindowState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(window);
}

void WindowState::ProcessEvent(Engine &engine, sf::Event &event) {
	window.ProcessEvent(engine, event);
}