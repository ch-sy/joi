#include "resourceManager.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "aseprite.h"

namespace fs = std::filesystem;


void ResourceManager::loadSprites(std::string sprite_path) {
	std::cout << "Loading sprites...\n";
	for (const auto & entry : std::filesystem::directory_iterator(sprite_path)) {
		std::string sprite_name = entry.path().filename().stem().string();
		std::cout << sprite_name << ": ";
		if (decodeAseprite(sprites[sprite_name], entry.path().string())) {
			std::cout << "OK\n";
		}
	}
}

const Aseprite& ResourceManager::getSprite(std::string sprite_name) {
	return sprites[sprite_name];
}