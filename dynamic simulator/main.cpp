#include "GL\glew.h"
#include "GL\freeglut.h"

#include "scenes.h"

Scene* scene;
void show(){
	scene->display();
}


void idleFunc(){
	scene->idle();
}

void keyFunc(unsigned char c, int x, int y) {
	scene->key_handle(c, x, y);
}
void mouse_move_func(int x, int y) {
	scene->on_mouse_move(x, y);
}
void mouse_click_handle(int button, int state, int x, int y) {
	scene->mouse_click_handle(button, state, x, y);

}
int main(int argc,char** argv){
	//scene = new Assimp_Scene();
	scene = new SceneWithLamp();
	//scene = new Plane();
	//scene = new Cubic_Box();
	//scene = new Triangle();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);


	glutInitWindowPosition(scene->window_init_x, scene->window_init_y);
	glutInitWindowSize( scene->Width,scene->Height);
	glViewport(scene->viewport_init[0], scene->viewport_init[1], scene->viewport_init[2], scene->viewport_init[3]);
	//glViewport(0, 0, 100, 100);
	glutCreateWindow("hello world");

	glewInit();
	scene->init();
	//glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
	glutDisplayFunc(show);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyFunc);
	glutMotionFunc(mouse_move_func);
	glutMouseFunc(mouse_click_handle);
	glutMainLoop();
	return 0;
}


