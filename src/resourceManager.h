#pragma once
#include "glad/glad.h"

#include <string>
#include <unordered_map>
#include "Aseprite.h"
#include "shader.h"

class ResourceManager {
private:
	std::unordered_map<std::string, Aseprite> sprites;
	std::unordered_map<std::string, Shader> shaders;
public:
	void loadSprites(std::string sprite_path);
	void loadShaders(std::string shader_path);
	const Aseprite* getSprite(std::string sprite_name);
	Shader getShader(std::string shader_name);
};