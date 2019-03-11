#include "resourceManager.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "aseprite.h"

namespace fs = std::filesystem;

void ResourceManager::loadSprites(std::string sprite_path) {
	for (const auto & entry : std::filesystem::directory_iterator(sprite_path)) {
		std::cout << "Loading: " << entry.path() << std::endl;
		Aseprite test;
		if (decodeAseprite(test, "..\\sprites\\munchkin.aseprite")) {
			std::cout << "Success!\n";
			std::cout << "Width: " << test.dimension.x << " Height: " << test.dimension.y << std::endl;
			std::cout << "Layers:\n";
			for (AsepriteLayer& layer : test.layers)
				std::cout << layer.layer_name << std::endl;
		}
		else
			std::cout << "Failure!\n";
	}
		
}

const Sprite& ResourceManager::getSprite(std::string sprite_name) {
	return sprites[sprite_name];
}