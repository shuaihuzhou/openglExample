#ifndef _PI_H
#define PI (3.1415926)
#endif

#include "ShZring.h"

ring::ring()
{
	m_current = 0;
	m_start = clock();
	m_current = 0;
	m_totalTime = 5;
	m_R = 0.2;
	m_numberPoint = 50;
	offsetAngle = 2*PI/m_numberPoint;
	m_typeName = "ring";
	m_view.SetLookAt(0,0,m_R,0,0,0,0,1,0);
}

ring::~ring()
{
}

void ring::getR(GLdouble &r)
{
	r = m_R;
}

void ring::setR(GLdouble r)
{
	m_R = r;
}

void ring::getTypeName(string &p)
{
	p = m_typeName;
}

void ring::setTypeName(const char* p)
{
	m_typeName = p;
}

void ring::setTotalTime(double totalTime)
{
	m_totalTime = totalTime;
}

void ring::begin()
{
	m_start = clock();
}

void ring::end()
{
	m_start = 0;
	m_current = 0;
}

void ring::clear()
{
	m_vertices.clear();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

void ring::init()
{
	//init the vertice;
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices.push_back(VECTOR3D(m_R * cos(i*offsetAngle), m_R * sin(i * offsetAngle), 0));  
	}

	//m_vertices_temp
	m_vertices_temp = m_vertices;

	//index of right face
	int middlePoint = m_numberPoint>>1;
	for (int i=0; i<middlePoint; i++)
	{
		m_index_r.push_back(i);
	}
	m_index_r.push_back(middlePoint);

	//index of left face
	for (int i=middlePoint; i<m_numberPoint; i++)
	{
		m_index_l.push_back(i);
	}
		m_index_l.push_back(0);

	// init the angle of left face
	int sizeFacel = m_index_l.size();
	for (int i=0; i<sizeFacel; i++)
	{
		m_angle_sl.push_back(0);
	}

	// init the angle of right face
	int sizeFacer = m_index_r.size();
	for (int i=0; i<sizeFacer; i++)
	{
		m_angle_sr.push_back(0);
	}

}

void ring::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	drawfaceL(pShader);
	drawfaceR(pShader);
	pShader->end();
}

void ring::unfold()
{
	unfoldL();
	unfoldR();
}

void ring::fold()
{
	foldL();
	foldR();
}

void ring::unfoldL()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4, temp5, temp6;
		int sizeFacel = m_index_l.size();
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFacel; i++)
		{
			m_angle_sl[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * (sizeFacel - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,0,1));
		temp2.SetRotationAxis(180,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,-m_R,0));
		temp6.SetTranslation(VECTOR3D(0,m_R,0));

		for (unsigned int i=0; i< m_index_l.size(); i++)
		{
			
			temp4.SetRotationAxis(-m_angle_sl[i],VECTOR3D(0,0,1));
			temp5.SetTranslation(VECTOR3D(-m_R * m_angle_sl[i] * PI / 180 + 2 * m_R * sin(m_angle_sl[i] * PI / 180), 0, 0));

			m_vertices[m_index_l[i]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_l[i]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);

		
	}
}

void ring::unfoldR()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		int sizeFacer = m_index_r.size();
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFacer; i++)
		{
			m_angle_sr[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime *  i * offsetAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,0,1));
		temp2.SetRotationAxis(180,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,-m_R,0));
		temp6.SetTranslation(VECTOR3D(0,m_R,0));

		
		for (unsigned int i=0; i< m_index_r.size(); i++)
		{

			temp4.SetRotationAxis(m_angle_sr[i],VECTOR3D(0,0,1));
			temp5.SetTranslation(VECTOR3D(m_R *  m_angle_sr[i] * PI / 180 - 2 * m_R * sin(m_angle_sr[i] * PI / 180),0,0));

			m_vertices[m_index_r[i]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_r[i]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);
	}
}

void ring::foldL()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
		int sizeFacel = m_index_l.size();
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFacel; i++)
		{
			m_angle_sl[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * (sizeFacel - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,0,1));
		temp2.SetRotationAxis(180,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,-m_R,0));
		temp8.SetTranslation(VECTOR3D(0,m_R,0));

		for (int i=0; i< (int)m_index_l.size(); i++)
		{
			temp4.SetRotationAxis(-(sizeFacel - 1 - i) * offsetAngle_l_degree,VECTOR3D(0,0,1));
			temp5.SetTranslation(VECTOR3D(-m_R * (sizeFacel - 1 - i) * offsetAngle_l_degree * PI / 180 + 2 * m_R * sin ((sizeFacel - 1 - i) * offsetAngle_l_degree * PI / 180), 0, 0));

			temp6.SetTranslation(VECTOR3D(m_R * m_angle_sl[i] * PI / 180 - 2 * m_R * sin(m_angle_sl[i] * PI / 180), 0, 0));
			temp7.SetRotationAxis(m_angle_sl[i],VECTOR3D(0,0,1));

			m_vertices[m_index_l[i]] = temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_l[i]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);


	}
}

void ring::foldR()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
		int sizeFacer = m_index_r.size();
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFacer; i++)
		{
			m_angle_sr[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * i * offsetAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,0,1));
		temp2.SetRotationAxis(180,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,-m_R,0));
		temp8.SetTranslation(VECTOR3D(0,m_R,0));

		for (int i=0; i< (int)m_index_r.size(); i++)
		{
			temp4.SetRotationAxis(i * offsetAngle_r_degree,VECTOR3D(0,0,1));
			temp5.SetTranslation(VECTOR3D(m_R * i * offsetAngle_r_degree * PI / 180 - 2 * m_R * sin(i * offsetAngle_r_degree * PI / 180), 0, 0));

			temp6.SetTranslation(VECTOR3D(-m_R * m_angle_sr[i] * PI / 180 + 2 * m_R * sin(m_angle_sr[i] * PI / 180), 0, 0));
			temp7.SetRotationAxis(-m_angle_sr[i],VECTOR3D(0,0,1));

			m_vertices[m_index_r[i]] = temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_r[i]];
		}



		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);


	}
}

void ring::drawfaceL(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	GLuint ebo1;
	glGenBuffers(1,&ebo1);
	GLuint modelLocaiton, viewLocation, projectionLocation;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_l.size() * sizeof(GL_UNSIGNED_INT), m_index_l.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_l);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_LINE_STRIP,m_index_l.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);

}

void ring::drawfaceR(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	GLuint ebo2;
	glGenBuffers(1,&ebo2);
	GLuint modelLocaiton, viewLocation, projectionLocation;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_r.size() * sizeof(GL_UNSIGNED_INT), m_index_r.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_r);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_LINE_STRIP,m_index_r.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo2);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

