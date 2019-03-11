#include "joi.h"

bool Joi::init() {
	if (glfwInit() == GLFW_FALSE)
		return false;
	
	resources.loadSprites("..\\sprites");
	const Aseprite& sprite = resources.getSprite("spr_munchkin");
	std::cout << "Breite: " << sprite.layers[0].layer_name << std::endl;

	window = glfwCreateWindow(1024, 768, "Journey on ice", NULL, NULL);
	if (window == NULL)
		return false;

	return true;
}

bool Joi::step() {

	return true;
}

bool Joi::render() {

	return true;
}

bool Joi::end() {
	glfwTerminate();

	return true;
}

bool Joi::run() {
	init();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		render();
		step();
	}
	end();

	return true;
}