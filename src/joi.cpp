#include "joi.h"

void Joi::init() {
	glfwInit();
	window = glfwCreateWindow(1024, 768, "Journey on ice", nullptr, nullptr);
}

void Joi::step() {

}

void Joi::render() {

}

void Joi::end() {
	glfwTerminate();
}

void Joi::run() {
	init();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		render();
		step();
	}
	end();
}