#pragma once
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct AsepriteFrame {
	glm::u16	duration;
};

struct AsepriteTag {
	glm::u16	duration;
};

struct AsepriteLayer {
	std::string	layer_name;
};

struct Aseprite {
	glm::u16vec2				dimension;
	std::vector<AsepriteFrame>	frames;
	std::vector<AsepriteLayer>	layers;
};


// Reference: https://github.com/aseprite/aseprite/blob/master/docs/ase-file-specs.md
bool decodeAseprite(Aseprite& aseprite, const char* file);