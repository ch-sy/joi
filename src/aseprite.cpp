#include "aseprite.h"

#define READ_NUMBER(val) is.read(reinterpret_cast<char*>(&val), sizeof(val))

void read_string(std::ifstream& is, std::string& str) {
	glm::u16 string_length;
	READ_NUMBER(string_length);
	str.resize(string_length);
	is.read(str.data(), string_length);
}

// Reference: https://github.com/aseprite/aseprite/blob/master/docs/ase-file-specs.md
bool decodeAseprite(Aseprite& aseprite, const char* file) {
	std::ifstream is(file, std::ios::binary);
	if (is.fail()) {
		std::cout << "Failed to open aseprite file";
		is.close();
		return 0;
	}

	is.seekg(4, std::ios_base::cur);
	// Magic number check
	glm::u16 magic_number;
	READ_NUMBER(magic_number);
	if (magic_number != 0xA5E0) {
		std::cout << "Aseprite's magic number of the main header doesn't match!\n";
		is.close();
		return false;
	}
	glm::u16 num_frames;
	READ_NUMBER(num_frames);
	aseprite.frames.resize(num_frames);
	READ_NUMBER(aseprite.dimension);
	// Color depth check
	glm::u16 color_depth;
	READ_NUMBER(color_depth);
	if (color_depth != 32) {
		std::cout << "Colordepth of " << color_depth << "bpp isn't supported. Use 32 bpp (RGBA)\n";
		is.close();
		return false;
	}
	is.seekg(114, std::ios_base::cur);
	// Iterate through each frame in the file
	for (glm::u16 frame_id = 0; frame_id < num_frames; frame_id++) {
		is.seekg(4, std::ios_base::cur);
		// Magic number check
		glm::u16 magic_number;
		READ_NUMBER(magic_number);
		if (magic_number != 0xF1FA) {
			std::cout << "Aseprite's magic number of frame " << frame_id << " doesn't match!\n";
			is.close();
			return false;
		}
		glm::u16 num_chunks_old;
		READ_NUMBER(num_chunks_old);
		READ_NUMBER(aseprite.frames[frame_id].duration);
		is.seekg(2, std::ios_base::cur);
		glm::u32 num_chunks;
		READ_NUMBER(num_chunks);
		if (num_chunks == 0)
			num_chunks = num_chunks_old;
		// Iterate through each chunk in this frame
		for (glm::u32 chunk_id = 0; chunk_id < num_chunks; chunk_id++) {
			glm::u32 chunk_size;
			READ_NUMBER(chunk_size);
			glm::u16 chunk_type;
			READ_NUMBER(chunk_type);
			switch (chunk_type) {
			case 0x2004: { // Layer Chunk
				is.seekg(16, std::ios_base::cur);
				std::string layer_name;
				read_string(is, layer_name);
				aseprite.layers.push_back({ layer_name });
			}
			break;
			default:
				is.seekg(chunk_size - 6, std::ios_base::cur);
			}
		}
	}
	is.close();
	return true;
}