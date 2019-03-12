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
		Aseprite& sprite = sprites[sprite_name];
		if (!decodeAseprite(sprite, entry.path().string()))
			continue;
		// Load texture to GPU
		for (auto &cel : sprite.cels) {
			glGenTextures(1, &cel.texture_id);
			glBindTexture(GL_TEXTURE_2D, cel.texture_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cel.dimension.x, cel.dimension.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, cel.pixel_data.data());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		std::cout << "Ok\n";
	}

}

void ResourceManager::loadShaders(std::string shader_path) {
	std::cout << "Loading shaders...\n";
	for (const auto & entry : std::filesystem::directory_iterator(shader_path)) {
		std::string shader_name = entry.path().filename().stem().string();
		
		if (shaders.count(shader_name) == 0) {
			std::cout << shader_name << ": ";
			Shader shader(entry.path().stem().string()+".vs", entry.path().stem().string() + ".fs");
			shaders[shader_name] = shader;
		}
	}
}

const Aseprite* ResourceManager::getSprite(std::string sprite_name) {
	if(sprites.count(sprite_name) > 0)
		return &sprites[sprite_name];
	else {
		std::cout << "Sprite \"" << sprite_name << "\" doesn't exists!";
		return nullptr;
	}
}

const Shader ResourceManager::getShader(std::string shader_name) {
	return shaders[shader_name];
}