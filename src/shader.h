#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h" // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

GLint loadShader(std::string vertexPath, std::string fragmentPath);
class Shader {
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader() {};
	Shader(std::string vertexPath, std::string fragmentPath);
	// use/activate the shader
	void use() const;
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVector(const std::string &name, const glm::vec4 &value) const;
	void setVector(GLint loc, const glm::vec4 &value) const;
	void setMatrix(const std::string &name, const glm::mat3 &value) const;
	void setMatrix(const std::string &name, const glm::mat4 &value) const;
	GLint getLoc(const std::string &name) const;
private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif