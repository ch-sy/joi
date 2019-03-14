#include "glad/glad.h"
#include "sprite.h"
#include <GLFW/glfw3.h>
#include "resourceManager.h"

class Joi {
	private:
		GLFWwindow * window;
		ResourceManager resources;
		GLuint vertexbuffer;
		SpriteRenderer renderer;
		Shader shd_default;

		bool init();
		bool step();
		
		bool end();
	public:
		bool render();
		bool run();
};