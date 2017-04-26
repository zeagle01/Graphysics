#ifndef SCENE_H
#define SCENE_H
#include <iostream>

#include "soil.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"


#include "shader.h"
#include "Array_Reader.h"
#include "camara.h"


	class Scene {
	public:
		const GLuint window_init_x = 100;
		const GLuint window_init_y = 100;
		const GLuint Height = 600;
		const GLuint Width = 800;
		const GLuint viewport_init[4] = { 0, 0, 100, 100 };
		virtual void display() = 0;
		virtual void init() = 0;
		virtual void idle() = 0;
		virtual  void key_handle(unsigned char c,int x,int y) {}
		virtual  void on_mouse_move(int x, int y) {}
		virtual void mouse_click_handle(int button, int state, int x, int y) {}

	};


	





#endif 