
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "scene.h"
#include "Array_Reader.h"


	class Triangle :public Scene {
		Shader* shader;
		GLuint VAO, VBO;
		GLuint EBO;
			int verts_size;
			float *verts;
		int trangle_size;
		int* tri;
	public:
		virtual void init() {

			shader = new Shader(".\\shaders\\triangle.vs", ".\\shaders\\triangle.frag");
			read_obj<GLfloat>(".\\test_data_files\\4_vertex_2_triangle.zobj", verts_size, verts, trangle_size, (int*&)tri);
			//verts=read<float>(".\\test_data_files\\4_vertex.vbo", verts_size);

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verts_size*8 , verts, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*trangle_size * 3, tri, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
			glEnableVertexAttribArray(0);


			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);


		}

		virtual void display() {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glClear(GL_COLOR_BUFFER_BIT);
			shader->use();

			glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, verts_size*3 );
			glDrawElements(GL_TRIANGLES, trangle_size*3, GL_UNSIGNED_INT,0 );
			glBindVertexArray(0);
			glutSwapBuffers();
		}
		virtual void idle() {

		}
	};

#endif