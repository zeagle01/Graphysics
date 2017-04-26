
#ifndef SHADER_H
#define  SHADER_H


#include <string>
#include "GL\glew.h"
#include "GL\freeglut.h"

using namespace std;

class Shader{
public:
	GLuint shader_program;
	const char* vertex_shader_code;
	const char* fragment_shader_code;
	Shader(const string& vertex_shader_file, const string& fragment_shader_file);

	void use();
	GLint get_uniform_variable(const string& variable_name);

};

#endif