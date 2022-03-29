//
// Created by nedo on 13.03.2022.
//

#ifndef GAMEPROTOTYPE_RESOURCEMANAGER_HPP
#define GAMEPROTOTYPE_RESOURCEMANAGER_HPP

#include <unordered_map>
#include <functional>
#include <filesystem>
#include <optional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Motion/DataSource.hpp>
#include "Logger.hpp"
#include "Settings/CursorPack.hpp"

template<class T>
using ContainerType = std::unordered_map<std::string, T>;

class ResourceManager {
public:
	explicit ResourceManager(const std::string& directoryName);
	[[nodiscard]] const std::string &GetResourceDirectory() const;

	sf::Texture& GetTexture(const std::string& name);
	sf::Font& GetFont(const std::string& name);
	sf::SoundBuffer& GetSoundBuffer(const std::string& name);
	sf::Music& GetMusic(const std::string& name);
	std::shared_ptr<sf::Shader>& GetShader(const std::string& name, const std::string& fragmentName, const std::string& vertexName);
	std::shared_ptr<mt::DataSource>& GetVideo(const std::string& name);
	const std::string& GetDocument(const std::string& name);
	CursorPack& GetCursorPack(const std::string& name);
private:

	template<class T>
	T& Loader(std::unordered_map<std::string, T>& container, const std::function<void(const std::string&)>& loader, const std::string& resourceName, const std::string& resourceType, const std::vector<std::string>& possibleExtensions)
	{
		if(container.contains(resourceName)) return container[resourceName];

		SPDLOG_DEBUG("Searching for resource \"{}\" ({})", resourceName, resourceType);
		auto result = FindFile(resourceName, possibleExtensions);
		if(!result.has_value())
			throw std::runtime_error(fmt::format("Could not find {} with name \"{}\"!", resourceType, resourceName));
		else
			loader(*result);

		return container[resourceName];
	}

	std::optional<std::string> FindFile(const std::string& name, const std::vector<std::string>& possibleExtensions);

	ContainerType<sf::Texture> textures;
	ContainerType<sf::Font> fonts;
	ContainerType<sf::SoundBuffer> sounds;
	ContainerType<sf::Music> music;
	ContainerType<CursorPack> cursorPacks;
	ContainerType<std::shared_ptr<sf::Shader>> shaders;
	ContainerType<std::shared_ptr<mt::DataSource>> videos;
	ContainerType<std::string> documents;

	ContainerType<std::string> shadersFragment;
	ContainerType<std::string> shadersVertex;

	std::string resourceDirectory;
};


#endif //GAMEPROTOTYPE_RESOURCEMANAGER_HPP
