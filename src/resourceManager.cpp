#include "resourceManager.h"
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

void ResourceManager::loadSprites(std::string sprite_path) {
	for (const auto & entry : std::filesystem::directory_iterator(sprite_path))
		std::cout << entry.path() << std::endl;
}

const Sprite& ResourceManager::getSprite(std::string sprite_name) {
	return sprites[sprite_name];
}