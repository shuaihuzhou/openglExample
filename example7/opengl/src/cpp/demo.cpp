#include "glew.h"
#include <stdlib.h>
#include "glut.h"
#include <iostream>
#include <time.h>
#include "cube.h"
using namespace std;

void display();
void reshape(int w,int h);
void init();
void animation();
//void animation();
double angle =0;
/*
clock_t start=0,current=0;
double totalTime = 5;*/
cube cube1;

GLfloat vertices[]={
	-0.125,-0.125,-0.125, //vertex 0
	-0.125,-0.125,0.125, //vertex 1
	-0.125,0.125,0.125, //vertex 2
	-0.125,0.125,-0.125, //vertex 3
	0.125,-0.125,-0.125, //vertex 4
	0.125,-0.125,0.125, //vertex 5
	0.125,0.125,0.125, //vertex 6
	0.125,0.125,-0.125 //vertex 7
};

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
	GLuint vboVertex;
	glGenBuffers(1,&vboVertex);
	glBindBuffer(GL_ARRAY_BUFFER,vboVertex);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(0);
}

void display()
{
	//clear the window
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	cube1.draw();
	
	//flush
	glFlush();
}




void animation()
{
	cube1.unfold();	
}

void reshape(int width,int height)
{
	//define the viewPort transformation
	glViewport(0,0,width,height);
}