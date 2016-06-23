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
	gluOrtho2D(-2,2.0,-2.0,2.0);
}

void display()
{
	//clear the window
	glClear(GL_COLOR_BUFFER_BIT);

	//draw scene
	//glColor3f(1,);
	GLint vertices[]={-1,1,
										1,1,
										1,-1,
										-1,-1
										};
	GLfloat color[]={
										1.0,1.0,0,
										1.0,1.0,0,
										1.0,0,0,
										1.0,0,0
									};
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2,GL_INT,0,vertices);
	glColorPointer(3,GL_FLOAT,0,color);
	
	glPointSize(15);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_BLEND);
// 	glBegin(GL_POINTS);
// 		glArrayElement(0);
// 		glArrayElement(1);
// 		glArrayElement(2);
// 		glArrayElement(3);
// 	glEnd();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_POINTS,0,4);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_BLEND)

	//flush
	glFlush();
}

void reshape(int width,int height)
{
	//define the viewPort transformation
	glViewport(0,0,width,height);
}