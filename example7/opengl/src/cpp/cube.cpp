#include "cube.h"

GLubyte index1[]={
	0,1,1,2,2,3,3,0 //left
};
GLubyte index2[]={
	0,3,3,7,7,4,4,0 //back
};
GLubyte index3[]={
	4,7,7,6,6,5,5,4 //right
};
GLubyte index4[]={
	1,2,2,6,6,5,5,1 //front
};
GLubyte index5[]={
	2,3,3,7,7,6,6,2 //up
};
GLubyte index6[]={
	0,1,1,5,5,4,4,0 //down
};

cube::cube()
{
	m_current = 0;
	m_start = clock();
	m_current = 0;
	m_totalTime = 10;
	m_anglel = 0;
	m_angler = 0;
	m_anglef = 0;
	m_angleb = 0;
	m_angleu = 0;
	m_angled = 0;

}

cube::~cube()
{

}

void cube::draw()
{
	drawfacel();
	drawfacer();
	drawfacef();
	drawfaceb();
	drawfaceu();
	drawfaced();
}

void cube::unfold()
{
	unfoldl();
	unfoldr();
	unfoldf();
	unfoldb();
	unfoldu();
	unfoldd();
	glutPostRedisplay();
}

void cube::unfoldl()
{
	m_current = clock();
	if ((m_current - m_start) < 10000)
	{
		m_anglel = (m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;
		//glutPostRedisplay();
	}
}

void cube::unfoldr()
{
	m_current = clock();
	if ((m_current - m_start) < 10000)
	{
		m_angler = (m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;
		//glutPostRedisplay();
	}
}

void cube::unfoldf()
{
	
}

void cube::unfoldb()
{
	m_current = clock();
	if ((m_current - m_start) < 20000 && (m_current - m_start) > 10000)
	{
		f_x = 0;
		f_y = 0.125;
		f_z = -0.125;
		f_x2 = 0;
		f_y2 = 0;
		f_z2 = 0;
		m_angleb = (m_current - (m_start + 10000) )/CLOCKS_PER_SEC/m_totalTime * 90;
		m_angleb2 = 0;
		//glutPostRedisplay();
	}

	if ((m_current - m_start) < 30000 && (m_current - m_start) > 20000)
	{
		f_x = 0;
		f_y = 0.125;
		f_z = -0.125;
		f_x2 = 0;
		f_y2 = 0.25;
		f_z2 = 0;
		m_angleb = 90;
		m_angleb2 = (m_current - (m_start + 20000) )/CLOCKS_PER_SEC/m_totalTime * 90;
		//glutPostRedisplay();
	}

}

void cube::unfoldu()
{
	m_current = clock();
	if ((m_current - m_start) < 30000 && (m_current - m_start) > 20000)
	{
		m_angleu = (m_current - (m_start + 20000))/CLOCKS_PER_SEC/m_totalTime * 90;
		//glutPostRedisplay();
	}
}

void cube::unfoldd()
{
	m_current = clock();
	if ((m_current - m_start) < 30000 && (m_current - m_start) > 20000)
	{
		m_angled = (m_current - (m_start + 20000))/CLOCKS_PER_SEC/m_totalTime * 90;
		//glutPostRedisplay();
	}
}

void cube::drawfacel()
{
	GLuint ebo1;
	glGenBuffers(1,&ebo1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index1),index1,GL_STATIC_DRAW);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	gluLookAt(0.125,0.125,0.125,-0.125,-0.125,-0.125,0,1,0);
	glTranslatef(-0.125,0,0.125);
	glRotatef(m_anglel,0,1,0);
	glTranslatef(0.125,0,-0.125);
	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);

	glPopMatrix();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);
	
}

void cube::drawfaceb()
{
	GLuint ebo2;
	glGenBuffers(1,&ebo2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index2),index2,GL_STATIC_DRAW);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	gluLookAt(0.125,0.125,0.125,-0.125,-0.125,-0.125,0,1,0);

	glTranslatef(f_x,f_y,f_z); //step 1
	glRotatef(m_angleb,1,0,0);
	

	glTranslatef(f_x2,f_y2,f_z2); //step 2
	glRotatef(m_angleb2,1,0,0);

	glTranslatef(-f_x2,-f_y2,-f_z2);
	glTranslatef(-f_x,-f_y,-f_z);

	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);


	glPopMatrix();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo2);

}

void cube::drawfacer()
{
	GLuint ebo3;
	glGenBuffers(1,&ebo3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index3),index3,GL_STATIC_DRAW);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	gluLookAt(0.125,0.125,0.125,-0.125,-0.125,-0.125,0,1,0);
	glTranslatef(0.125,0,0.125);
	glRotatef(-m_angler,0,1,0);
	glTranslatef(-0.125,0,-0.125);
	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);

	glPopMatrix();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo3);

}

void cube::drawfacef()
{
	GLuint ebo4;
	glGenBuffers(1,&ebo4);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index4),index4,GL_STATIC_DRAW);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	gluLookAt(0.125,0.125,0.125,-0.125,-0.125,-0.125,0,1,0);
	glTranslatef(-0.125,0,0.125);
	glRotatef(m_anglef,0,1,0);
	glTranslatef(0.125,0,-0.125);
	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);

	glPopMatrix();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	
	glDeleteBuffers(1,&ebo4);

}

void cube::drawfaceu()
{
	GLuint ebo5;
	glGenBuffers(1,&ebo5);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index5),index5,GL_STATIC_DRAW);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	gluLookAt(0.125,0.125,0.125,-0.125,-0.125,-0.125,0,1,0);
	glTranslatef(0,0.125,0.125);
	glRotatef(m_angleu,1,0,0);
	glTranslatef(0,-0.125,-0.125);
	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);

	glPopMatrix();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo5);

}

void cube::drawfaced()
{
	GLuint ebo6;
	glGenBuffers(1,&ebo6);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index6),index6,GL_STATIC_DRAW);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	gluLookAt(0.125,0.125,0.125,-0.125,-0.125,-0.125,0,1,0);
	glTranslatef(0,-0.125,0.125);
	glRotatef(-m_angled,1,0,0);
	glTranslatef(0,0.125,-0.125);
	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);

	glPopMatrix();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo6);

}