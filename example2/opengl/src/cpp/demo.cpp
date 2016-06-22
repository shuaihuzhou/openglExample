#include "glut.h"
#include <iostream>
using namespace std;

void display();
void reshape(int w,int h);
void init();
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

	init();

	//begin glut internal loop
	glutMainLoop();
	return 0;
}

void init()
{
	glClearColor(0,0,0,0);
	//define the projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1.0,-1.0,1.0,-5,5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	//clear the window
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-5,0,0,0,0,1,0);
	//draw scene
	glColor3f(1,1,1);
	glutWireTeapot(0.5);

	//flush
	glFlush();
}

void reshape(int width,int height)
{
	//define the viewPort transformation
	glViewport(0,0,width,height);
}