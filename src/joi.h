#include "glad/glad.h"
#include "sprite.h"
#include <GLFW/glfw3.h>
#include "resourceManager.h"

class Joi {
	private:
		GLFWwindow * window;
		ResourceManager resources;

		bool init();
		bool step();
		bool render();
		bool end();
	public:
		bool run();
};