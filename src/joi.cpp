#include "joi.h"

bool Joi::init() {
	if (glfwInit() == GLFW_FALSE)
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	
	window = glfwCreateWindow(1024, 768, "Journey on ice", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	resources.loadSprites("..\\sprites");
	std::cout << "\n";
	resources.loadShaders("..\\shaders");

	return true;
}

bool Joi::step() {

	return true;
}

bool Joi::render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	return true;
}

bool Joi::end() {
	glfwTerminate();

	return true;
}

bool Joi::run() {
	init();
	while (!glfwWindowShouldClose(window)) {
		render();
		glfwSwapBuffers(window);
		step();
		glfwPollEvents();
	}
	end();

	return true;
}