//
// Created by nedo on 21.03.2022.
//

#include "Config.hpp"
#include "../Logger.hpp"
using namespace pugi;

Config::Config(const std::string &documentPath) { // NOLINT(cppcoreguidelines-pro-type-member-init)
	this->documentPath = documentPath;
}

void Config::Load() {
	xml_parse_result result = document.load_file(documentPath.c_str());
	if(!result) {
		SPDLOG_CRITICAL("Failed to load config from \"{}\"!", documentPath);
		std::abort();
	}

	auto configNode = document.child("Config");
	auto firstLaunchAttribute = configNode.attribute("FirstLaunch");
	firstLaunch = firstLaunchAttribute.as_bool(true);
}

void Config::Create() {
	auto configNode = document.append_child("Config");
	auto firstLaunchNodeAttribute = configNode.append_attribute("FirstLaunch");
	firstLaunchNodeAttribute.set_value(true);

	Save();
}

void Config::Save() {
	document.save_file(documentPath.c_str());
}

const pugi::xml_document &Config::GetDocument() const {
	return document;
}

bool Config::IsFirstLaunch() const {
	return firstLaunch;
}

void Config::SetFirstLaunch(bool firstLaunch) {
	document.child("Config").attribute("FirstLaunch").set_value(firstLaunch);
	this->firstLaunch = firstLaunch;
}
