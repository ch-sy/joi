#pragma once
#include "shader.h"
#include "glad/glad.h"
#include "aseprite.h"


class SpriteRenderer {
public:
	void drawSprite(const Shader &shader, const Aseprite& sprite, glm::vec2 position, int frame = 0) const;
	void initRenderData();
private:
	Shader shader;
	GLuint vertexbuffer;
	GLuint vao;
};