#include "glut.h"
#include <iostream>
using namespace std;

void display();
void reshape(int w,int h);
void init();
void mouse(int button,int state,int x, int y);
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);
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
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);

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

int spin=0;

void display()
{
	//clear the window
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1,1,1);
	//glRotatef(spin,0,1,0);

	glutWireTeapot(0.5);
	

	//flush
	glFlush();
}

void reshape(int width,int height)
{
	//define the viewPort transformation
	glViewport(0,0,width,height);
}

void mouse(int button,int state,int x, int y)
{
	switch (button)
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			spin = 2;
			glRotatef(spin,x,y,0);
			glutPostRedisplay();
		}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'A':
			{
				spin = 2;
				glRotatef(spin,x,y,0);
				glutPostRedisplay();
				break;
			}
		case 'S':
			{
				glScalef(0.2,0.2,0.2);
				glutPostRedisplay();
				break;
			}
		case 'B':
			{
				glScalef(5,5,5);
				glutPostRedisplay();
				break;
			}
	}
}

void motion(int x, int y)
{
	spin = 2;
	glRotatef(spin,x,y,0);
	glutPostRedisplay();
}