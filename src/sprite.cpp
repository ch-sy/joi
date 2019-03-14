#include "sprite.h"

void SpriteRenderer::drawSprite(const Shader &shader, const Aseprite &sprite, glm::vec2 position, int frame) const {
	if(sprite.frames.size() > 0)
	for (auto &cel : sprite.frames[frame % sprite.frames.size()].cel_ids) {
		glm::mat4 mat_model = { 
			sprite.cels[cel].dimension.x, 0.0f, 0.0f, 0.0f,
			0.0f, sprite.cels[cel].dimension.y, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			position.x + sprite.cels[cel].position.x, position.y + sprite.cels[cel].position.y, 0.0f, 1.0f };
		//glm::mat4 mat_model = glm::mat4(1);
		//mat_model *= glm::vec4(sprite->cels[cel_id].dimension, 0.0f, 1.0f);

		shader.setMatrix("model", mat_model);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBindTexture(GL_TEXTURE_2D, sprite.cels[cel].texture_id);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	
}

void SpriteRenderer::initRenderData() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	static const glm::vec2 g_vertex_buffer_data[] = {
		glm::vec2(0,0),	glm::vec2(0,0),
		glm::vec2(1,0),	glm::vec2(1,0),
		glm::vec2(0,1),	glm::vec2(0,1),
		glm::vec2(1,1),	glm::vec2(1,1),
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)(2 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
}