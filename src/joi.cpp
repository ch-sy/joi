#include "joi.h"
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
	resize_context->render();
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

	/*static const glm::vec2 g_vertex_buffer_data[] = {
		glm::vec2(0,0),	glm::vec2(0,0),
		glm::vec2(1,0),	glm::vec2(1,0),
		glm::vec2(0,1),	glm::vec2(0,1),
		glm::vec2(1,1),	glm::vec2(1,1),
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);*/

	

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

bool Joi::render() {
	float pixel_size = glm::round(g_width / 256.0f);
	if (pixel_size < 1)
		pixel_size = 1;
	
	glm::mat4 projection_view = glm::ortho(0.0f, float(g_width) / pixel_size, float(g_height) / pixel_size, 0.0f);
	glUniformMatrix4fv(uni_projection_view, 1, false, glm::value_ptr(projection_view));
	glClearColor(0.0f, 0.05f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	const Aseprite& fnt_good_neighbors = resources.getSprite("fnt_good_neighbors");
	renderer.drawSprite(fnt_good_neighbors, glm::vec2(16, 16));
	const Aseprite& spr_old_hut = resources.getSprite("spr_old_hut");
	renderer.drawSprite(spr_old_hut, glm::vec2(16, 64), glfwGetTime()*10);
	glfwSwapBuffers(window);
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
		step();
		glfwPollEvents();
	}
	end();

	return true;
}