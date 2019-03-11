#include "aseprite.h"
#include <map>
#include <string>

#define READ_NUMBER(val) is.read(reinterpret_cast<char*>(&val), sizeof(val))

void read_string(std::ifstream& is, std::string& str) {
	glm::u16 string_length;
	READ_NUMBER(string_length);
	str.resize(string_length);
	is.read(str.data(), string_length);
}

struct CelAppearance {
	glm::u16 frame_id;
	glm::u16 layer_id;
};

inline bool operator<(const CelAppearance& v1, const CelAppearance& v2) {
	if (v1.frame_id != v2.frame_id)
		return v1.frame_id < v2.frame_id;
	else
		return v1.layer_id < v2.layer_id;
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
	std::map<CelAppearance, glm::u16> cel_appearances;	// (frame_id | layer_id), cel_id
	std::vector<glm::u16vec3> cel_link_appearances;		// (frame_id | frame_to_link | layer)
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
			case 0x2005: { // Cel Chunk
				glm::u16 layer_id;
				READ_NUMBER(layer_id);
				glm::i16vec2 position;
				READ_NUMBER(position);
				is.seekg(1, std::ios_base::cur);
				glm::u16 cel_type;
				READ_NUMBER(cel_type);
				is.seekg(7, std::ios_base::cur);
				switch (cel_type) {
				case 0: { // Raw Cel
					AsepriteCel cel;
					cel.position = position;
					cel.layer_id = layer_id;
					READ_NUMBER(cel.dimension);
					size_t pixel_count = cel.dimension.x * cel.dimension.y;
					cel.pixel_data.resize(pixel_count);
					is.read(reinterpret_cast<char*>(cel.pixel_data.data()), pixel_count * 4);
					const glm::u16 cel_id = glm::u16(aseprite.cels.size());
					// Save the cel in this sprite
					aseprite.cels.push_back(cel);
					// Save where you can find the first cel
					cel_appearances[{frame_id, layer_id}] = cel_id;
					// Link this frame with the new cel
					aseprite.frames[frame_id].linked_cel_ids.push_back(cel_id);
				}
				break;
				case 1: // Linked Cel
					glm::u16 frame_position;
					READ_NUMBER(frame_position);
					// Search later on for this cell
					cel_link_appearances.push_back(glm::u16vec3(frame_id, frame_position, layer_id));
				break;
				case 2: { // Compressed Image

				}
				break;
				}
			}
			break;
			default:
				is.seekg(chunk_size - 6, std::ios_base::cur);
			}
		}
	}
	// Save the links in the frames with the cell id
	for (glm::u16vec3 &to_link : cel_link_appearances) {
		aseprite.frames[to_link.x].linked_cel_ids.push_back(cel_appearances[{to_link.y, to_link.z}]);
	}
	is.close();
	return true;
}