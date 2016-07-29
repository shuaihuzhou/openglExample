#ifndef _PI_H
#define PI (3.1415926)
#endif 

#include "ShZpolygon.h"

polygon::polygon()
{
	m_current = 0;
	m_start = clock();
	m_current = 0;
	m_totalTime = 3;
	m_R = 0.3;
	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;
	m_numberPoint = 5;
	offsetAngle = 2*PI/m_numberPoint;
	m_typeName = "polygon";
	m_view.SetLookAt(0,0,m_R,0,0,0,0,1,0);
}

polygon:: ~polygon()
{

}

void polygon::getPosition(GLdouble &positionX, GLdouble &positionY, GLdouble &positionZ)
{
	positionX = m_positionX;
	positionY = m_positionY;
	positionZ = m_positionZ;
}

void polygon::setPosition(GLdouble positionX, GLdouble positionY, GLdouble positionZ)
{
	m_positionX = positionX;
	m_positionY = positionY;
	m_positionZ = positionZ;
}

void polygon::getEdges(GLdouble &edges)
{
	edges = this->m_numberPoint;
}

void polygon::setEdges(GLdouble edges)
{
	this->m_numberPoint = edges;
	offsetAngle = 2*PI/m_numberPoint;
}

void polygon::getR(GLdouble &r)
{
	r = this->m_R;
}

void polygon::setR(GLdouble r)
{
	this->m_R = r;
}

void polygon::getTypeName(string &p)
{
	p = m_typeName;
}

void polygon::setTypeName(const char* p)
{
	m_typeName = p;
}

void polygon::setTotalTime(double totalTime)
{
	m_totalTime = totalTime;
}

void polygon::clear()
{
	m_vertices.clear();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

void polygon::begin()
{
	m_start = clock();
}

void polygon::end()
{
	m_start = 0;
	m_current = 0;
}

void polygon::init()
{

	//init the vertices;
	m_vertices.push_back(VECTOR3D(0,0,0));
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices.push_back(VECTOR3D(m_positionX + m_R * cos(i*offsetAngle), m_positionY + m_R * sin(i*offsetAngle), m_positionZ));
	}

	//index
	m_index.push_back(0);
	for (int i=1; i<m_numberPoint+1; i++)
	{
		m_index.push_back(i);
	}
	m_index.push_back(1);


	//init VAO VBO
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//glDrawArrays(GL_polygon_FAN,0,8);

	/*glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);*/

	glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void polygon::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	glBindVertexArray(m_vao);
	drawface(pShader);
	glBindVertexArray(0);
	pShader->end();
}

void polygon::unfold()
{
	unfoldface();
}

void polygon::fold()
{
	foldface();
}

void polygon::unfoldface()
{
	cout<<"sorry polygon can't be unfolded"<<endl;
}

void polygon::foldface()
{
	cout<<"sorry polygon can't be folded"<<endl;
}


void polygon::drawface(ShZshader *pShader)
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

	glDrawElements(GL_TRIANGLE_FAN, m_index.size(), GL_UNSIGNED_INT,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);

}