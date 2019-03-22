#pragma once
#include "shader.h"
#include "glad/glad.h"
#include "aseprite.h"
#include <glm/gtc/type_ptr.hpp>

class SpriteRenderer {
public:
	void drawSprite(const Aseprite& sprite, glm::vec2 position, int frame = 0) const;
	void drawText(const Aseprite& sprite, glm::vec2 position, const std::string& text) const;
	int getTextWidth(const Aseprite &sprite, const std::string& text) const;
	void initRenderData(GLint shader);
private:
	GLint shader;
	GLint uni_model_vector;
};

class Renderer {

};


// Controls how to draw the sprite on the screen
class GSprite {
public:
	GSprite(Renderer &renderer, const char* sprite_name);
	void setPosition(glm::vec2 pos);
	void startAnimation(const char* animation_name);
private:
	glm::vec2 pos;
};

// Controls how to draw the text on the screen
class GText {
};