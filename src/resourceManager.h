#pragma once
#include <string>
#include <map>
#include "sprite.h"

class ResourceManager {
private:
	std::map<std::string, Sprite> sprites;
public:
	void loadSprites(std::string sprite_path);
	const Sprite& getSprite(std::string sprite_name);
};