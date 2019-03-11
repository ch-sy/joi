#pragma once
#include <string>
#include <unordered_map>
#include "Aseprite.h"

class ResourceManager {
private:
	std::unordered_map<std::string, Aseprite> sprites;
public:
	void loadSprites(std::string sprite_path);
	const Aseprite& getSprite(std::string sprite_name);
};