#include "sprite.h"


void SpriteRenderer::drawSprite(const Aseprite &sprite, glm::vec2 position, int frame) const {
	glUniform2fv(uni_model_vector, 1, glm::value_ptr(position));
	const AsepriteFrame& aseFrame = sprite.frames[frame % sprite.frames.size()];
	for (auto &cel : aseFrame.cel_ids) {
		glBindTexture(GL_TEXTURE_2D, sprite.cels[cel].texture_id);
		glDrawArrays(GL_TRIANGLE_STRIP, sprite.cels[cel].vertex_id, 4);
	}
}

void SpriteRenderer::initRenderData(GLint shader) {
	this->shader = shader;
	uni_model_vector = glGetUniformLocation(shader, "model");
}