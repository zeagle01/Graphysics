#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Shader::Shader(const string& vertex_shader_file, const string& fragment_shader_file){
	ifstream v_s_fin;
	ifstream f_s_fin;
	v_s_fin.open(vertex_shader_file);
	if (!v_s_fin) {
		cout << "fail to open vertex source file" << endl;
	}
	f_s_fin.open(fragment_shader_file);
	if (!f_s_fin) {
		cout << "fail to open fragment source file" << endl;
	}
	stringstream v_s_stream, f_s_stream;
	v_s_stream << v_s_fin.rdbuf();
	f_s_stream << f_s_fin.rdbuf();


	string vertex_shader_code_as_string(v_s_stream.str());
	vertex_shader_code = vertex_shader_code_as_string.c_str();
	string fragment_shader_code_as_string(f_s_stream.str());
	fragment_shader_code = fragment_shader_code_as_string.c_str();
	//cout << vertex_shader_code << endl;
	//cout << fragment_shader_code << endl;

	GLuint verts_shader;
	verts_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(verts_shader, 1, &vertex_shader_code, NULL);
	glCompileShader(verts_shader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(verts_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(verts_shader, 512, NULL, infoLog);
		cout << "error vertex shader compilation at "<<vertex_shader_file << endl;
		cout << infoLog << endl;
	}

	
	GLuint fragement_shader;
	fragement_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragement_shader, 1, &fragment_shader_code, NULL);
	glCompileShader(fragement_shader);
	glGetShaderiv(fragement_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragement_shader, 512, NULL, infoLog);
		cout << "error fragment shader compilation at " <<fragment_shader_file<< endl;
		cout << infoLog << endl;
	}


	shader_program = glCreateProgram();
	glAttachShader(shader_program, verts_shader);
	glAttachShader(shader_program, fragement_shader);
	glLinkProgram(shader_program);

		glGetShaderiv(shader_program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader_program, 512, NULL, infoLog);
			cout << "error shader program linking" << endl;
			cout << infoLog << endl;
		}

	glDeleteShader(verts_shader);
	glDeleteShader(fragement_shader);

}


void Shader::use(){
	glUseProgram(shader_program);
}

GLint Shader::get_uniform_variable(const string & variable_name)
{
	return glGetUniformLocation(shader_program, variable_name.c_str());
}
