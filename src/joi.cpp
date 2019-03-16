#include "joi.h"
#include <fmt/format.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int g_width = 1024;
int g_height = 768;

Joi* resize_context;
void window_size_callback(GLFWwindow* window, int width, int height) {
	if (window == NULL)
		return;
	g_width = width;
	g_height = height;
	glViewport(0, 0, width, height);
	resize_context->render(0.0f);
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

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	resources.loadSprites("..\\sprites");
	std::cout << "\n";
	resources.loadShaders("..\\shaders");

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)(2 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shd_default = resources.getShader("shd_default");
	glUseProgram(shd_default);
	uni_projection_view = glGetUniformLocation(shd_default, "proj_view");
	renderer.initRenderData(shd_default);

	return true;
}

bool Joi::step() {

	return true;
}

bool Joi::render(double frame_time) {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	float pixel_size = glm::round(g_width / 320.0f);
	if (pixel_size < 1)
		pixel_size = 1;
	
	glm::mat4 projection_view = glm::ortho(0.0f, float(g_width) / pixel_size, float(g_height) / pixel_size, 0.0f);
	glUniformMatrix4fv(uni_projection_view, 1, false, glm::value_ptr(projection_view));
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	const Aseprite& fnt_good_neighbors = resources.getSprite("fnt_good_neighbors");
	renderer.drawText(fnt_good_neighbors, glm::vec2(4, 4), fmt::format("FT: {:.2f}ms", 1000*frame_time));
	renderer.drawText(fnt_good_neighbors, glm::vec2(4, 20), fmt::format("Test", 1000 * frame_time));
	const Aseprite& spr_old_hut = resources.getSprite("spr_old_hut");
	renderer.drawSprite(spr_old_hut, glm::vec2(16, 16), glfwGetTime()*10);
	glfwSwapBuffers(window);
	return true;
}

bool Joi::end() {
	glfwTerminate();

	return true;
}

bool Joi::run() {
	init();
	double previousTime = glfwGetTime();
	int time_frame = 0;
	const int scale = 1000;
	double times[scale];
	
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		times[(time_frame++) % scale] = currentTime - previousTime;
		double d_time = 0.0;
		for (int i = 0; i < scale; i++)
			d_time += times[i];
		render(d_time / scale);
		step();
		glfwPollEvents();
		previousTime = currentTime;
	}
	end();

	return true;
}