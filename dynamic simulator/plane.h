#ifndef PLANE_H
#define PLANE_H

#include "scene.h"
#include <random>
#include <chrono>
#include <limits>

	void init_texture(GLuint& texture, const string& texture_file) {
		int width, height;
		unsigned char* image = SOIL_load_image(texture_file.data(), &width, &height, 0, SOIL_LOAD_RGB);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	class Plane :public Scene {
	protected:
		Shader* shader;
		mt19937 mt_rand;
		int verts_size;
		int trangle_size;
		GLfloat* verts = NULL; //nullptr;
		GLuint* tri = nullptr;
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		GLuint texture0;
		GLuint texture1;
		Array_Reader* array_reader;
	public:

		virtual void init() {
			init_texture(texture0, ".\\textures\\container.jpg");
			//init_texture(texture1, ".\\textures\\awesomeface.png");
			init_texture(texture1, ".\\textures\\converges.jpg");

			shader = new Shader(".\\shaders\\plane.vs", ".\\shaders\\plane.frag");
			array_reader = new Array_Reader();
			read_obj<GLfloat>(".\\test_data_files\\4_vertex_2_triangle.zobj", verts_size, verts, trangle_size, (int*&)tri);

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verts_size * 8, verts, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*trangle_size * 3, tri, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			shader->use();

			auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
			mt_rand.seed(seed);
		}
		virtual void display() {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0);
			glUniform1i(glGetUniformLocation(shader->shader_program, "our_tex0"), 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glUniform1i(glGetUniformLocation(shader->shader_program, "our_tex1"), 1);
			shader->use();

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, trangle_size*3, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glutSwapBuffers();
		}
		virtual void idle() {
			GLfloat time_value = mt_rand()*1.0f / numeric_limits<unsigned int>::max();
			GLuint var_loc;
			glm::mat4 model;
			model = glm::rotate(model, 5.0f*time_value, glm::vec3(1, 0, 0));
			var_loc = shader->get_uniform_variable("model");
			glUniformMatrix4fv(var_loc, 1, GL_FALSE, glm::value_ptr(model));

			glm::mat4 view;
			view = glm::translate(view, glm::vec3(0, 0, -3));
			var_loc = shader->get_uniform_variable("view");
			glUniformMatrix4fv(var_loc, 1, GL_FALSE, glm::value_ptr(view));

			glm::mat4 projection;
			projection = glm::perspective(45.0f, GLfloat(Width) / GLfloat(Height), 0.1f, 100.0f);
			var_loc = shader->get_uniform_variable("projection");
			glUniformMatrix4fv(var_loc, 1, GL_FALSE, glm::value_ptr(projection));

			glutPostRedisplay();
		}
	};



	class Cubic_Box :public Plane {

			GLfloat time_value = 0;
			vector<glm::vec3> cubePositions = {
				glm::vec3(0.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  5.0f, -15.0f),
				glm::vec3(-1.5f, -2.2f, -2.5f),
				glm::vec3(-3.8f, -2.0f, -12.3f),
				glm::vec3(2.4f, -0.4f, -3.5f),
				glm::vec3(-1.7f,  3.0f, -7.5f),
				glm::vec3(1.3f, -2.0f, -2.5f),
				glm::vec3(1.5f,  2.0f, -2.5f),
				glm::vec3(1.5f,  0.2f, -1.5f),
				glm::vec3(-1.3f,  1.0f, -1.5f)
			};
			
			camara_np::Camara* camara = new camara_np::Walking_Camara();

		virtual void init() {
			init_texture(texture0, ".\\textures\\container.jpg");
			init_texture(texture1, ".\\textures\\awesomeface.png");

			shader = new Shader(".\\shaders\\cubic.vs", ".\\shaders\\cubic.frag");
			array_reader = new Array_Reader();
			read_obj<GLfloat>(".\\test_data_files\\cubic_vertex_array.vbo", verts_size, verts, trangle_size, (int*&)tri);

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verts_size * 5, verts, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			shader->use();

			glEnable(GL_DEPTH_TEST);
			auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
			mt_rand.seed(seed);
		}

		virtual void display() {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glClear(GL_COLOR_BUFFER_BIT);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0);
			glUniform1i(glGetUniformLocation(shader->shader_program, "our_tex0"), 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glUniform1i(glGetUniformLocation(shader->shader_program, "our_tex1"), 1);
			shader->use();
			auto cam_pos = camara->cam_pos;
			auto cam_front = camara->cam_front;
			auto cam_up = camara->cam_up;
			for (int i = 0; i < cubePositions.size(); i++) {
				GLuint var_loc;
				glm::mat4 model;
				GLfloat model_rotate_rate = 1e1;
				model = glm::translate(model, cubePositions[i]);
				model = glm::rotate(model, model_rotate_rate*time_value, glm::vec3(0.5, 1, 0));
				var_loc = shader->get_uniform_variable("model");
				glUniformMatrix4fv(var_loc, 1, GL_FALSE, glm::value_ptr(model));

				glm::mat4 view;
				view = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
				var_loc = shader->get_uniform_variable("view");
				glUniformMatrix4fv(var_loc, 1, GL_FALSE, glm::value_ptr(view));

				glm::mat4 projection;
				projection = glm::perspective(45.0f, GLfloat(Width) / GLfloat(Height), 0.1f, 100.0f);
				var_loc = shader->get_uniform_variable("projection");
				glUniformMatrix4fv(var_loc, 1, GL_FALSE, glm::value_ptr(projection));

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, verts_size * 3);
				glBindVertexArray(0);
			}

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, verts_size * 3);
				glBindVertexArray(0);
			glutSwapBuffers();
		}
		virtual void idle() {

			glutPostRedisplay();
			time_value += 1.0;
		}
		virtual  void key_handle(unsigned char c,int x,int y) {
			camara->key_handle(c, x, y);

		}
		virtual  void on_mouse_move(int x, int y) {
			camara->on_mouse_move(x, y);

			
		}
		virtual void mouse_click_handle(int button, int state, int x, int y) {
			camara->mouse_click_handle(button, state, x, y);
			
		}
	};


#endif