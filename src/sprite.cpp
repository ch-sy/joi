#include "sprite.h"


void SpriteRenderer::drawSprite(const Aseprite &sprite, glm::vec2 position, int frame) const {
	glUniform2fv(uni_model_vector, 1, glm::value_ptr(position));
	const AsepriteFrame& aseFrame = sprite.frames[frame % sprite.frames.size()];
	for (auto &cel : aseFrame.cel_ids) {
		glBindTexture(GL_TEXTURE_2D, sprite.cels[cel].texture_id);
		glDrawArrays(GL_TRIANGLE_STRIP, sprite.cels[cel].vertex_id, 4);
	}
}

void SpriteRenderer::drawText(const Aseprite &sprite, glm::vec2 position, const std::string& text) const {
	glBindTexture(GL_TEXTURE_2D, sprite.cels[0].texture_id);
	for (auto ch : text) {
		std::string utf8_char = {ch};
		if (ch == ' ') {
			position.x += sprite.slices.at("space").dimension.x;
			continue;
		}
		glUniform2fv(uni_model_vector, 1, glm::value_ptr(position));
		try {
			const AsepriteSlice& slice = sprite.slices.at(utf8_char);
			glDrawArrays(GL_TRIANGLE_STRIP, slice.vertex_id, 4);
			position.x += slice.dimension.x - slice.pivot.x;
		}
		catch (...) {
			std::cout << "Char " << utf8_char << " not found\n";
		}
		
	}
}

int SpriteRenderer::getTextWidth(const Aseprite &sprite, const std::string& text) const {
	int width = 0;
	for (auto ch : text) {
		std::string utf8_char = { ch };
		if (ch == ' ') {
			width += sprite.slices.at("space").dimension.x;
			continue;
		}
		try {
			const AsepriteSlice& slice = sprite.slices.at(utf8_char);
			width += slice.dimension.x - slice.pivot.x;
		}
		catch (...) {
			std::cout << "Char " << utf8_char << " not found\n";
		}

	}
	return width;
}

void SpriteRenderer::initRenderData(GLint shader) {
	this->shader = shader;
	uni_model_vector = glGetUniformLocation(shader, "model");
}