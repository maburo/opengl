/*
 * Shader.h
 *
 *  Created on: 15 окт. 2018 г.
 *      Author: alex
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>

class Shader {
public:
	GLuint program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual ~Shader();

	void use();
};

#endif /* SHADER_H_ */
