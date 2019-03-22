#pragma once
#include "glad/glad.h"

#include <string>
#include <unordered_map>
#include <map>
#include "Aseprite.h"
#include "shader.h"

class ResourceManager {
private:
	std::map<std::string, Aseprite> sprites;
	GLuint cel_vertex_buffer;
	std::unordered_map<std::string, GLint> shaders;
	const Aseprite spr_null;
public:
        ResourceManager(){};
	void loadSprites(std::string sprite_path);
	void loadShaders(std::string shader_path);
	const Aseprite& getSprite(const std::string &sprite_name) const;
	GLint getShader(std::string shader_name) const;
};