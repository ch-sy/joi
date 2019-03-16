#include "resourceManager.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "aseprite.h"

namespace fs = std::filesystem;


void ResourceManager::loadSprites(std::string sprite_path) {
	std::cout << "Sprites\n";
	std::vector<glm::vec2> vertex_buffer_data;
	for (const auto & entry : std::filesystem::directory_iterator(sprite_path)) {
		std::string sprite_name = entry.path().filename().stem().string();
		std::cout << ">> " << sprite_name << ": ";
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
			const glm::vec2 pos = cel.position;
			const glm::vec2 dim = cel.dimension;

			cel.vertex_id = vertex_buffer_data.size()/2;
			vertex_buffer_data.push_back(pos);
			vertex_buffer_data.push_back(glm::vec2(0.0f, 0.0f));

			vertex_buffer_data.push_back(pos + glm::vec2(dim.x, 0.0f));
			vertex_buffer_data.push_back(glm::vec2(1.0f, 0.0f));

			vertex_buffer_data.push_back(pos + glm::vec2(0.0f, dim.y));
			vertex_buffer_data.push_back(glm::vec2(0.0f, 1.0f));

			vertex_buffer_data.push_back(pos + dim);
			vertex_buffer_data.push_back(glm::vec2(1.0f, 1.0f));
		}
		std::cout << "\t\tOk\n";
	}

	glGenBuffers(1, &cel_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, cel_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*vertex_buffer_data.size(), vertex_buffer_data.data(), GL_STATIC_DRAW);
}

void ResourceManager::loadShaders(std::string shader_path) {
	std::cout << "Shaders\n";
	for (const auto & entry : std::filesystem::directory_iterator(shader_path)) {
		std::string shader_name = entry.path().filename().stem().string();
		if (shaders.count(shader_name) == 0) {
			std::string s_p_n = shader_path + "\\" + shader_name;
			std::cout << ">> " << shader_name << ": ";
			shaders[shader_name] = loadShader(s_p_n + ".vert", s_p_n + ".frag");
		}
	}
}

const Aseprite& ResourceManager::getSprite(const std::string &sprite_name) const {
	try {
		return sprites.at(sprite_name);
	}
	catch (...) {
		std::cout << "Sprite \"" << sprite_name << "\" doesn't exists!\n";
		return spr_null;
	}
}

GLint ResourceManager::getShader(std::string shader_name) const {
	try {
		return shaders.at(shader_name);
	}
	catch (...) {
		std::cout << "Shader \"" << shader_name << "\" doesn't exists!\n";
		throw std::out_of_range("Shader not found!");
	}
}