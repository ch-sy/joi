#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "resourceManager.h"
#include "sprite.h"
#include <glog/logging.h>

class Joi {
 private:
  GLFWwindow *window;
  ResourceManager resources;
  GLuint vertexbuffer;
  SpriteRenderer renderer;
  GLint shd_default;
  GLint uni_projection_view;
  GLuint vao;

  bool init();
  bool step();

  bool end();

 public:
  Joi(){};
  bool render(double frame_time);
  bool run();
};
