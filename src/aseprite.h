#pragma once
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <vector>

enum LoopAnimationDirection : glm::u8 {
	lad_forward,
	lad_reverse,
	lad_ping_pong
};

struct AsepriteFrame {
	glm::u16					duration;
	std::vector<glm::u16>		linked_cel_ids;
};

struct AsepriteLayer {
	std::string					layer_name;
};


struct AsepriteCel {
	glm::u16					layer_id;
	glm::i16vec2				position;
	glm::u16vec2				dimension;
	std::vector<glm::u8vec4>	pixel_data;
};

struct AsepriteTag {
	glm::u16					from_frame_id;
	glm::u16					to_frame_id;
	LoopAnimationDirection		animation_dir;
	std::string					tag_name;
};

struct Aseprite {
	glm::u16vec2				dimension;
	std::vector<AsepriteFrame>	frames;
	std::vector<AsepriteLayer>	layers;
	std::vector<AsepriteCel>	cels;
	std::vector<AsepriteTag>	tags;
};


// Reference: https://github.com/aseprite/aseprite/blob/master/docs/ase-file-specs.md
bool decodeAseprite(Aseprite& aseprite, const char* file);