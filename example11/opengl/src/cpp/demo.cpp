#include "glew.h"
#include <stdlib.h>
#include "glut.h"
#include <iostream>
#include <time.h>
#include "ShZshapeManager.h"
using namespace std;

ShZshapeManager sm;
void createShape();
void drawShape();
void clearShape();
void animation();
void display();
void reshape(int w,int h);
void init();
//int cnt =0;

int main(int arg,char **argv)
{
	//init the glut which is responsible for handling windows and user iteraction
	glutInit(&arg,argv);

	//init the position, size, display mode for a new window
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_RGBA);
	
	//create and set up a window
	glutCreateWindow("hello glut");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(animation);

	glewInit();
	init();


	//begin glut internal loop
	glutMainLoop();
	return 0;
}

void init()
{
	glClearColor(0,0,0,0);
	sm.create_shape("ring");
	sm.begin("ring");
}

void display()
{
	//clear the window
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	
	sm.draw_shape("ring");

	//flush
	glFlush();
}




void animation()
{
	sm.unfold_shape("ring");
	sm.fold_shape("ring");
	glutPostRedisplay();
}

void reshape(int width,int height)
{
	//define the viewPort transformation
	glViewport(0,0,width,height);
}