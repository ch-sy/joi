#include "GLFW/glfw3.h"

class Joi {
	private:
		GLFWwindow * window;
		void init();
		void step();
		void render();
		void end();
	public:
		void run();
};