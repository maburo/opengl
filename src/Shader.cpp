/*
 * Shader.cpp
 *
 *  Created on: 15 окт. 2018 г.
 *      Author: alex
 */

#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream v;
	std::ifstream f;

	v.exceptions(std::ifstream::badbit);
	f.exceptions(std::ifstream::badbit);

	try {
		v.open(vertexPath);
		f.open(fragmentPath);

		std::stringstream vStream, fStream;

		vStream << v.rdbuf();
		fStream << f.rdbuf();

		v.close();
		f.close();

		vertexCode = vStream.str();
		fragmentCode = fStream.str();
	} catch (const std::ifstream::failure &e) {
		std::cout << "Error: shader file" << std::endl;
	}

	const GLchar* vCode = vertexCode.c_str();
	const GLchar* fCode = fragmentCode.c_str();

	GLint success;
	GLchar infoLog[512];

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error: Vertex shader compilation failed" << std::endl;
	}

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error: Fragment shader compilation failed" << std::endl;
	}

	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(this->program);

	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->program, 512, NULL, infoLog);
		std::cout << "Error: Program linkage failed" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(this->program);
}

Shader::~Shader() {}

