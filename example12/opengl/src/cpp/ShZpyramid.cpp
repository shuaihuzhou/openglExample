#ifndef _PI_H
#define PI (3.1415926)
#endif 

#include "ShZpyramid.h"

pyramid::pyramid()
{
	m_current = 0;
	m_start = clock();
	m_current = 0;
	m_totalTime = 3;
	m_R = 0.5;
	m_H = 0.6;
	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;
	m_viewPosition = VECTOR3D(m_positionX - m_R, m_positionY, m_positionZ);
	m_lightPosition = VECTOR3D(m_positionX, m_positionY - m_H, m_positionZ);

	m_lightColor = VECTOR3D(1,1,1);
	m_objectColor = VECTOR3D(1,0,0);
	m_numberPoint = 3;
	offsetAngle = 2*PI/m_numberPoint;
	m_typeName = "pyramid";
	m_view.SetLookAt(m_R,0,m_R/m_numberPoint,0,-m_H/2,0,0,1,0);
}

pyramid:: ~pyramid()
{

}

void pyramid::getPosition(GLdouble &positionX, GLdouble &positionY, GLdouble &positionZ)
{
	positionX = m_positionX;
	positionY = m_positionY;
	positionZ = m_positionZ;
}

void pyramid::setPosition(GLdouble positionX, GLdouble positionY, GLdouble positionZ)
{
	m_positionX = positionX;
	m_positionY = positionY;
	m_positionZ = positionZ;
}

void pyramid::getR(GLdouble &r)
{
	r = this->m_R;
}

void pyramid::setR(GLdouble r)
{
	this->m_R = r;
}

void pyramid::getH(GLdouble &h)
{
	h = this->m_H;
}

void pyramid::setH(GLdouble h)
{
	this->m_H = h;
}

void pyramid::getEdges(GLdouble &edges)
{
	edges = this->m_numberPoint;
}

void pyramid::setEdges(GLdouble edges)
{
	this->m_numberPoint = edges;
	offsetAngle = 2*PI/m_numberPoint;
}

void pyramid::getTypeName(string &p)
{
	p = m_typeName;
}

void pyramid::setTypeName(const char* p)
{
	m_typeName = p;
}

void pyramid::setTotalTime(double totalTime)
{
	m_totalTime = totalTime;
}

void pyramid::clear()
{
	m_vertices.clear();
	m_index.clear();
	m_normals.clear();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);
}

void pyramid::begin()
{
	m_start = clock();
}

void pyramid::end()
{
	m_start = 0;
	m_current = 0;
}

void pyramid::init()
{

	//init the vertices;
	m_vertices.push_back(VECTOR3D(m_positionX, m_positionY + m_H/2, m_positionZ));
	m_normals.push_back(VECTOR3D(0,1,0));
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices.push_back(VECTOR3D(m_positionX + m_R * cos(i*offsetAngle), -m_H/2 + m_positionY, m_positionZ + m_R * sin(i*offsetAngle)));
		m_normals.push_back(VECTOR3D(cos(i*offsetAngle), 0, sin(i*offsetAngle)));
	}

	//index
	for (int i=0; i<m_numberPoint+1; i++)
	{
		m_index.push_back(i);
	}
	m_index.push_back(1);


	//init VAO VBO
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);
	glGenBuffers(1,&m_nbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * 3 * sizeof(GL_FLOAT), m_normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void pyramid::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	glBindVertexArray(m_vao);
	drawface(pShader);
	glBindVertexArray(0);
	pShader->end();
}

void pyramid::unfold()
{
	unfoldface();
}

void pyramid::fold()
{
	foldface();
}

void pyramid::unfoldface()
{
	cout<<"sorry pyramid can't be unfolded"<<endl;
}

void pyramid::foldface()
{
	cout<<"sorry pyramid can't be folded"<<endl;
}


void pyramid::drawface(ShZshader *pShader)
{
	GLuint ebo1;
	glGenBuffers(1,&ebo1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index.size() * sizeof(GL_UNSIGNED_INT), m_index.data(), GL_STATIC_DRAW);


	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model);

	
	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_FAN, m_index.size(), GL_UNSIGNED_INT,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo1);

}