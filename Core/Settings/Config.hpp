//
// Created by nedo on 21.03.2022.
//

#ifndef GAMEPROTOTYPE_CONFIG_HPP
#define GAMEPROTOTYPE_CONFIG_HPP

#include <string>
#include "pugixml.hpp"

class Config {
public:
	explicit Config(const std::string& documentPath);
	Config() = default;
	void Load();
	void Create();
	void Save();

	[[nodiscard]] const pugi::xml_document &GetDocument() const;
	[[nodiscard]] bool IsFirstLaunch() const;

	void SetFirstLaunch(bool firstLaunch);

private:
	std::string documentPath;

	pugi::xml_document document;
	bool firstLaunch;
};


#endif //GAMEPROTOTYPE_CONFIG_HPP
