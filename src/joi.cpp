#include "joi.h"
#include <glm/gtc/matrix_transform.hpp>

int g_width = 1024;
int g_height = 768;

Joi* resize_context;
void window_size_callback(GLFWwindow* window, int width, int height) {
	g_width = width;
	g_height = height;
	glViewport(0, 0, width, height);
	resize_context->render();
	glfwSwapBuffers(window);
}

bool Joi::init() {
	resize_context = this;
	if (glfwInit() == GLFW_FALSE)
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	window = glfwCreateWindow(g_width, g_height, "Journey on ice", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, window_size_callback);
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	resources.loadSprites("..\\sprites");
	std::cout << "\n";
	resources.loadShaders("..\\shaders");

	shd_default = resources.getShader("shd_default");

	renderer.initRenderData();

	return true;
}

bool Joi::step() {

	return true;
}

bool Joi::render() {
	float pixel_size = glm::round(g_width / 256.0f);
	if (pixel_size < 1)
		pixel_size = 1;
	glm::mat4 projection_view = glm::ortho(0.0f, float(g_width) / pixel_size, float(g_height) / pixel_size, 0.0f);

	glClearColor(0.0f, 0.05f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	shd_default.setMatrix("projection_view", projection_view);
	shd_default.use();
	
	renderer.drawSprite(shd_default, resources.getSprite("fnt_good_neighbors"), glm::vec2(16, 16));
	renderer.drawSprite(shd_default, resources.getSprite("spr_old_hut"), glm::vec2(16, 64), glfwGetTime()*10);

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