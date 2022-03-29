//
// Created by nedo on 13.03.2022.
//

#include "ResourceManager.hpp"

#include <optional>
#include <fstream>

ResourceManager::ResourceManager(const std::string& directoryName) {
	SPDLOG_DEBUG("Searching for resource directory with name \"{}\".", directoryName);

	std::optional<std::filesystem::path> directory = std::nullopt;
	auto current = std::filesystem::current_path();

	while(current.has_parent_path() && current != current.root_path()) {
		for (auto &d: std::filesystem::directory_iterator(current))
		{
			if(d.is_directory() && d.path().filename().string() == directoryName)
			{
				directory = d;
				break;
			}
		}

		current = current.parent_path();
	}

	if(!directory.has_value())
		throw std::runtime_error(fmt::format("Could not find resource directory with name \"{}\"!", directoryName));

	SPDLOG_INFO("Resource directory is {}", directory->string());
	resourceDirectory = directory->string();
}

const std::string &ResourceManager::GetResourceDirectory() const {
	return resourceDirectory;
}

sf::Texture &ResourceManager::GetTexture(const std::string &name) {
	return Loader(textures, [this, &name](const std::string& path){textures[name].loadFromFile(path);}, name, "texture", {".png", ".jpg", ".jpeg"});
}

sf::Font &ResourceManager::GetFont(const std::string &name) {
	return Loader(fonts, [this, &name](const std::string& path){fonts[name].loadFromFile(path);}, name, "font", {".otf", ".ttf"});
}

sf::SoundBuffer &ResourceManager::GetSoundBuffer(const std::string &name) {
	return Loader(sounds, [this, &name](const std::string& path){sounds[name].loadFromFile(path);}, name, "sound buffer", {".wav", ".ogg"});
}

sf::Music &ResourceManager::GetMusic(const std::string &name) {
	return Loader(music, [this, &name](const std::string& path){music[name].openFromFile(path);}, name, "music", {".wav", ".ogg"});
}

std::shared_ptr<sf::Shader> &ResourceManager::GetShader(const std::string& name, const std::string &fragmentName, const std::string &vertexName) {
	if(!shaders.contains(name)) {
		auto fragment = FindFile(fragmentName, {".glsl"});
		auto vertex = FindFile(vertexName, {".glsl"});
		shaders[name] = std::make_shared<sf::Shader>();
		if(!fragment.has_value() || !vertex.has_value())
			throw std::runtime_error(fmt::format("Failed to load shader \"{}\" (one of the files were not found)! Fragment: {} | Vertex: {}", name, fragment.has_value() ? "found": "not found", vertex.has_value() ? "found": "not found"));
		else
			shaders[name]->loadFromFile(*vertex, *fragment);
	}
	return shaders[name];
}


	std::optional<std::string> ResourceManager::FindFile(const std::string &name, const std::vector<std::string>& possibleExtensions) {
	for(auto& file: std::filesystem::recursive_directory_iterator(resourceDirectory))
	{
		auto path = file.path();
		if(file.is_regular_file() && std::find(possibleExtensions.begin(), possibleExtensions.end(), path.extension().string()) != possibleExtensions.end() && path.stem().string() == name)
		{
			return path.string();
		}
	}
	return std::nullopt;
}

std::shared_ptr<mt::DataSource> &ResourceManager::GetVideo(const std::string &name) {
	return Loader(videos, [this, &name](const std::string& path){
		videos[name] = std::make_shared<mt::DataSource>();
		videos[name]->LoadFromFile(path);
	}, name, "video source", {".mp4", ".webm", ".avi"});
}

const std::string &ResourceManager::GetDocument(const std::string& name) {
	return Loader(documents, [this, &name](const std::string& path){
		documents[name] = path;
	}, name, "document", {".xml"});
}

CursorPack& ResourceManager::GetCursorPack(const std::string &name) {
	return Loader(cursorPacks, [this, &name](const std::string& path){
		cursorPacks[name].Load(this, path);
	}, name, "cursor pack", {".xml"});
}

