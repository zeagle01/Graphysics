#ifndef DRAWING_MESH_H
#define DRAWING_MESH_H

#include <vector>
#include <sstream>

#include "GL\glew.h"
#include "GL\freeglut.h"



#include "glm\glm.hpp"
#include <string>
using namespace std;
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture_coordinate;

};

struct Texture {
	GLuint id;
	string type;
	string path;
};

class DrawingMesh {
public:
	vector<Vertex> vertex;
	vector<GLuint> triangles;
	vector<Texture> texture;
	DrawingMesh() {  }
//	DrawingMesh(vector<Vertex> vertex, vector<GLuint> triangles, vector<Texture> texture) :
//	vertex(vertex),triangles(triangles),texture(texture){}
	void draw( Shader* shader) {
		shader->use();

		GLuint diffuseNr = 1;
		GLuint specularNr = 1;
		for (GLuint i = 0; i < this->texture.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
			// Retrieve texture number (the N in diffuse_textureN)
			stringstream ss;
			string number;
			string name = this->texture[i].type;
			if (name == "texture_diffuse")
				ss << diffuseNr++; // Transfer GLuint to stream
			else if (name == "texture_specular")
				ss << specularNr++; // Transfer GLuint to stream
			number = ss.str();

			glUniform1f(glGetUniformLocation(shader->shader_program, ("material." + name + number).c_str()), i);
			glBindTexture(GL_TEXTURE_2D, this->texture[i].id);
		}
		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,  triangles.size(),GL_UNSIGNED_INT,0);
		//glDrawArrays(GL_TRIANGLES, 0 ,9);
		glBindVertexArray(0);
	}

	void prepare_GL_buffer() {
		glGenVertexArrays(1,&VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);


		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertex.size(), &vertex[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*triangles.size(), &triangles[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (GLvoid*)(0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (GLvoid*)(offsetof(Vertex,normal)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (GLvoid*)(offsetof(Vertex,texture_coordinate)));
		glBindVertexArray(0);


	}
private:
	GLuint VAO, VBO, EBO;

	
};


#endif
