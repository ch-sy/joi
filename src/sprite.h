#pragma once
#include "shader.h"
#include "glad/glad.h"
#include "aseprite.h"
#include <glm/gtc/type_ptr.hpp>

class SpriteRenderer {
public:
	void drawSprite(const Aseprite& sprite, glm::vec2 position, int frame = 0) const;
	void drawText(const Aseprite& sprite, glm::vec2 position, const std::string& text) const;
	void initRenderData(GLint shader);
private:
	GLint shader;
	GLint uni_model_vector;
};