//
// Created by nedo on 16.03.2022.
//

#include "EngineHelper.hpp"
//#include "../States/LoadingState.hpp"
//#include "../States/IntroImageState.hpp"
#include "../States/BootingState.hpp"
#include "../States/MenuState.hpp"
void EngineHelper::StartupScenes(Engine &e) {
	e.AddState<MenuState>();
	if(e.GetConfig().IsFirstLaunch())
		e.AddState<BootingState>();
}
