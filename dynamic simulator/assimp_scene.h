

#ifndef ASSIMP_SCENE
#define ASSIMP_SCENE

#include "Importer.hpp"
#include "..\assimp\inc\scene.h"
#include "postprocess.h"

#include "scene.h"
#include "drawing_mesh.h"
#include "mesh_loader.h"

	class Assimp_Scene :public Scene{
	protected:	
		//string scene_file = ".\\test_data_files\\Nanosuit2\\nanosuit2.obj";
		string scene_file = ".\\test_data_files\\nanosuit\\nanosuit.obj";
		//string scene_file = ".\\test_data_files\\Blonde Elexis - nude\\Blonde Elexis - nude.obj";
		//string scene_file = ".\\test_data_files\\triangle.obj";
		vector<DrawingMesh> meshes;
		//Shader shader=Shader("assimp_model.vs", "assimp_model.frag");
		//Shader shader=Shader(".\\assimp_model.vs", ".\\assimp_model.frag");
		Shader* shader;//= Shader(".\\shaders\\plane.vs", ".\\shaders\\plane.frag");
		camara_np::Camara* camara = new camara_np::Walking_Camara();
		MeshLoader mesh_loader;

		void draw_meshes() {

			auto cam_pos = camara->cam_pos;
			auto cam_front = camara->cam_front;
			auto cam_up = camara->cam_up;

			shader->use();
			GLuint var_loc;
			glm::mat4 model;
			model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
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


			for (auto mesh : meshes) {
				mesh.draw(shader);
			}
		}
	public:
		virtual void display() {

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			draw_meshes();

			glutSwapBuffers();
		}
		virtual void init() {
			shader = new Shader(".\\shaders\\assimp_model.vs", ".\\shaders\\assimp_model.frag");
			mesh_loader.load_from_file(scene_file,meshes);
		}


		virtual void idle() {
			glutPostRedisplay();
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


	class SceneWithLamp :public Assimp_Scene {
	protected:
		glm::vec3 light_color = glm::vec3(1, 1, 1);
		string lamp_file=".\\test_data_files\\cube.obj";
		Shader* lamp_shader;//= Shader(".\\shaders\\plane.vs", ".\\shaders\\plane.frag");
		vector<DrawingMesh> lamp;
		void draw_lamp() {

			lamp_shader->use();
			auto cam_pos = camara->cam_pos;
			auto cam_front = camara->cam_front;
			auto cam_up = camara->cam_up;
			glm::mat4 model;
			model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
			model = glm::translate(model,glm::vec3(10,10,-5));
			// model = glm::translate(model,glm::vec3(1,1,-1));
			auto var_loc = lamp_shader->get_uniform_variable("model");
			glUniformMatrix4fv(var_loc, 1, GL_FALSE, glm::value_ptr(model));

			glm::mat4 view = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
			var_loc = lamp_shader->get_uniform_variable("view");
			glUniformMatrix4fv(var_loc, 1, GL_FALSE, glm::value_ptr(view));

			glm::mat4 projection = glm::perspective(45.0f, GLfloat(Width) / GLfloat(Height), 0.1f, 100.0f);
			var_loc = lamp_shader->get_uniform_variable("projection");
			glUniformMatrix4fv(var_loc, 1, GL_FALSE, glm::value_ptr(projection));


			for (auto mesh : lamp) {
				mesh.draw(lamp_shader);
			}
		}
	public:
		virtual void init() {
			shader = new Shader(".\\shaders\\assimp_model_with_lamp.vs", ".\\shaders\\assimp_model_with_lamp.frag");

			//string scene_file = ".\\test_data_files\\ball.obj";
			//string scene_file = ".\\test_data_files\\cube.obj";
			mesh_loader.load_from_file(scene_file,meshes);

			lamp_shader = new Shader(".\\shaders\\lamp.vs", ".\\shaders\\lamp.frag");

			mesh_loader.load_from_file(lamp_file,lamp);

			glEnable(GL_DEPTH_TEST);
		}

		virtual void display() {
			
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		//-------------draw mesh-----------------
			shader->use();
			auto light_color_loc=shader->get_uniform_variable("light_color");
			glUniform3f(light_color_loc, light_color.x, light_color.y, light_color.z);

			auto view_position_loc=shader->get_uniform_variable("view_position");
			glUniform3f(view_position_loc, camara->cam_pos.x,camara->cam_pos.y,camara->cam_pos.z);
			draw_meshes();

		//-------------draw lamp-----------------
			lamp_shader->use();
			light_color_loc=lamp_shader->get_uniform_variable("light_color");
			glUniform3f(light_color_loc, light_color.x, light_color.y, light_color.z);
			draw_lamp();

			glutSwapBuffers();
		}
	};


#endif