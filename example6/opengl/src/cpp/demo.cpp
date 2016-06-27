#include "glew.h"
#include <stdlib.h>
#include "glut.h"
#include <iostream>
using namespace std;

void display();
void reshape(int w,int h);
void init();

GLchar* vertextShaderSource = "#version 330 core \n"
	"layout (location = 0) in vec3 position; \n"
	"layout (location = 1) in vec3 color; \n"
	"out vec3 ourColor; \n"
	"void main() \n"
	"{\n"
	"gl_Position = vec4(position,1.0);\n"
	"ourColor = color;\n"
	"}\0";

GLchar* fragmentShaderSource = "#version 330 core \n"
	"in vec3 ourColor; \n"
	"out vec4 color; \n"
	"void main() \n"
	"{\n"
	"color = vec4(ourColor,0); \n"
	"}\0";

GLuint vao,vbo[3];

GLubyte index[]={0,1,2,0,3,1};

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

	//glDeleteVertexArrays(1,&vao);
	//glDeleteBuffers(2,vbo);
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
	gluOrtho2D(-1,1.0,-1.0,1.0);

	GLfloat vertices[]={-0.5,0.5,0,
		0.5,0.5,0,
		0.5,-0.5,0,
		-0.5,-0.5,0
	};
	GLfloat color[]={
		1.0,0,0,
		0,1.0,0,
		0,0,1.0,
		1.0,0,1.0

	};

	

	glGenVertexArrays(1,&vao);
	glGenBuffers(3,vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);

}

void display()
{
	//clear the window
	glClear(GL_COLOR_BUFFER_BIT);

	//build and compile shader
	//vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertextShaderSource,NULL);
	glCompileShader(vertexShader);

	//check compile error for vertex
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		cout<<"error:: shader:: vertex:: compile_failed\n"<<infoLog<<endl;
	}

	//fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);

	//check compile error for fragment
	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
		cout<<"error:: shader:: fragment:: compile_failed\n"<<infoLog<<endl;
	}

	//linking shader
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);

	//check linking error
	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
		cout<<"error:: shader:: program:: linking_failed\n"<<infoLog<<endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo[2]);

	//glPointSize(15);
	//glDrawArrays(GL_TRIANGLE_FAN,0,4);
	glDrawElements(GL_LINE_STRIP,6,GL_UNSIGNED_BYTE,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	//flush
	glFlush();

}

void reshape(int width,int height)
{
	//define the viewPort transformation
	glViewport(0,0,width,height);

}