#pragma once
#include "shader.h"
#include "glad/glad.h"
#include "aseprite.h"


class SpriteRenderer {
public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	void DrawSprite(Aseprite &sprite, glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	GLuint quadVAO;

	void initRenderData();
};