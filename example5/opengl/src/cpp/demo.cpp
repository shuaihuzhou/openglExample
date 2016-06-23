#include "glew.h"
#include <stdlib.h>
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

	glewInit();
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
										1.0,1.0,1.0,
										1.0,1.0,1.0,
										1.0,0,0,
										1.0,0,0
									};
	
	
	GLuint vbo[2];
	glGenBuffers(2,vbo);

	glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
	glBufferData(GL_ARRAY_BUFFER,8*sizeof(GLint),vertices,GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_INT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
	glBufferData(GL_ARRAY_BUFFER,12*sizeof(GLfloat),color,GL_STATIC_DRAW);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3,GL_FLOAT,0,0);
	
	
	glDrawArrays(GL_LINE_LOOP,0,4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDeleteBuffers(2,vbo);

	//flush
	glFlush();
}

void reshape(int width,int height)
{
	//define the viewPort transformation
	glViewport(0,0,width,height);
}