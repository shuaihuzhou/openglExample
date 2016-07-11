#define PI (3.1415926)
#include "ShZcylinder.h"

cylinder::cylinder()
{
	m_current = 0;
	m_start = clock();
	m_current = 0;
	m_totalTime = 3;
	m_angle_t = 0;
	m_angle_b = 0;
	m_angle_s = 0;
	m_R = 0.2;
	m_H = 0.5;
	m_numberPoint = 50;
	m_typeName = "cylinder";
	m_view.SetLookAt(m_R,m_H/2,m_R,0,0,0,0,1,0);
}

cylinder::~cylinder()
{
}

void cylinder::getRH(GLdouble &r,GLdouble &h)
{
	r = m_R;
	h = m_H;
}

void cylinder::setRH(GLdouble r, GLdouble h)
{
	m_R = r;
	m_H = h;
}

void cylinder::getTypeName(string &p)
{
	p = m_typeName;
}

void cylinder::setTypeName(const char* p)
{
	m_typeName = p;
}

void cylinder::setTotalTime(double totalTime)
{
	m_totalTime = totalTime;
}

void cylinder::begin()
{
	m_start = clock();
}

void cylinder::end()
{
	m_start = 0;
	m_current = 0;
}

void cylinder::clear()
{
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

void cylinder::init()
{
	//init the vertices;
	double offsetAngle = 2*PI/m_numberPoint;

	m_vertices.push_back(VECTOR3D(0, m_H/2, 0));
	m_vertices.push_back(VECTOR3D(0, -m_H/2, 0));
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices.push_back(VECTOR3D(m_R * cos(i*offsetAngle), m_H/2, m_R * sin(i * offsetAngle)));   //top face vertices
		m_vertices.push_back(VECTOR3D(m_R * cos(i*offsetAngle), -m_H/2, m_R * sin(i * offsetAngle)));  //bottom face vertices
	}

	//index of top face
	m_index_top.push_back(0);
	for (int i=2; i<(m_numberPoint<<1) + 2; i+=2)
	{
		m_index_top.push_back(i);
	}
	m_index_top.push_back(2);

	//index of bottom face
	m_index_bottom.push_back(1);
	for (int i=3; i<(m_numberPoint<<1) + 2; i+=2)
	{
		m_index_bottom.push_back(i);
	}
	m_index_bottom.push_back(3);

	//index of side face
	for (int i=2; i<(m_numberPoint<<1) + 2; i++)
	{
		m_index_side.push_back(i);
	}

	
	

	//init VAO VBO
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//glDrawArrays(GL_TRIANGLE_FAN,0,8);
	
	/*glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_b.size() * 3 * sizeof(GL_FLOAT), m_vertices_b.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT), m_vertices_s.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);*/
	
// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void cylinder::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	glBindVertexArray(m_vao);
	drawfacet(pShader);
	drawfaceb(pShader);
	drawfaces(pShader);
	glBindVertexArray(0);
	pShader->end();
}

void cylinder::unfold()
{
	unfoldt();
	unfoldb();
	unfolds();
}

void cylinder::fold()
{
	folds();
	foldt();
	foldb();	
}

void cylinder::unfolds()
{
	/*m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2;
		m_model_side.LoadIdentity();

		m_angle_s = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_side.SetTranslation(VECTOR3D(m_L/2,0,-m_W/2));
		temp1 = m_model_side;
		m_model_side.SetRotationAxis(m_angle_s,VECTOR3D(0,1,0));
		temp2 = m_model_side;
		m_model_side.SetTranslation(VECTOR3D(-m_L/2,0,m_W/2));
		m_model_side = m_model_side * temp2 * temp1;

		//glutPostRedisplay();
	}*/
}

void cylinder::unfoldt()
{

}

void cylinder::unfoldb()
{

}

void cylinder::folds()
{

}

void cylinder::foldt()
{

}

void cylinder::foldb()
{

}

void cylinder::drawfacet(ShZshader *pShader)
{
	GLuint ebo1;
	glGenBuffers(1,&ebo1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_top.size() * sizeof(GL_UNSIGNED_INT),m_index_top.data(),GL_STATIC_DRAW);

	cout<<m_index_top.size()<<endl;

	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_top);


	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_TRIANGLE_FAN,m_index_top.size(),GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);

}

void cylinder::drawfaceb(ShZshader *pShader)
{
	GLuint ebo2;
	glGenBuffers(1,&ebo2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_bottom.size() * sizeof(GL_UNSIGNED_INT),m_index_bottom.data(),GL_STATIC_DRAW);


	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_bottom);


	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_TRIANGLE_FAN,m_index_bottom.size(),GL_UNSIGNED_INT,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo2);

}

void cylinder::drawfaces(ShZshader *pShader)
{
	GLuint ebo3;
	glGenBuffers(1,&ebo3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_side.size() * sizeof(GL_UNSIGNED_INT),m_index_side.data(),GL_STATIC_DRAW);


	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_side);


	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_LINES,m_index_side.size(),GL_UNSIGNED_INT,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo3);

}