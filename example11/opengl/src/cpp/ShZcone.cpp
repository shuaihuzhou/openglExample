#ifndef _PI_H
#define PI (3.1415926)
#endif

#include "ShZcone.h"

cone::cone()
{
	m_current = 0;
	m_start = clock();
	m_current = 0;
	m_totalTime = 5;
	m_R = 0.3;
	m_H = 0.5;
	m_generatrix = sqrt(m_R * m_R + m_H * m_H);
	m_unfoldedAngle = 2*PI*m_R/m_generatrix;
	m_numberPoint = 50;
	offsetAngle = 2*PI/m_numberPoint;
	offsetNewAngle = m_unfoldedAngle/m_numberPoint;
	m_typeName = "cone";
	m_view.SetLookAt(m_R/2,m_H/2,m_R,0,0,0,0,1,0);
}

cone::~cone()
{
}

void cone::getRH(GLdouble &r, GLdouble &h)
{
	r = m_R;
	h = m_H;
}

void cone::setRH(GLdouble r, GLdouble h)
{
	m_R = r;
	m_H = h;
	m_generatrix = sqrt(m_R * m_R + m_H * m_H);
}

void cone::getTypeName(string &p)
{
	p = m_typeName;
}

void cone::setTypeName(const char* p)
{
	m_typeName = p;
}

void cone::setTotalTime(double totalTime)
{
	m_totalTime = totalTime;
}

void cone::begin()
{
	m_start = clock();
}

void cone::end()
{
	m_start = 0;
	m_current = 0;
}

void cone::clear()
{
	m_vertices.clear();
	m_vertices_temp.clear();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

void cone::init()
{
	//init the vertice;
	m_vertices.push_back(VECTOR3D(0,m_H/2,0));
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices.push_back(VECTOR3D(m_R * cos(i*offsetAngle), -m_H/2, m_R * sin(i * offsetAngle)));
	}

	//m_vertices_temp
	m_vertices_temp = m_vertices;

	//index of right side face
	int middlPoint = (m_numberPoint>>1) + 1;
	for (int i=0; i<middlPoint; i++)
	{
		m_index_sR.push_back(i);
	}
	m_index_sR.push_back(middlPoint);

	//index of left side inner face
	m_index_sL.push_back(0);
	for (int i=middlPoint; i<m_numberPoint+1; i++)
	{
		m_index_sL.push_back(i);
	}
		m_index_sL.push_back(1);

	// init the angle of right face
	int sizeFaceSR = m_index_sR.size();
	for (int i=0; i<sizeFaceSR; i++)
	{
		m_angle_sR_step1.push_back(0);
		m_angle_sR_step2.push_back(0);
	}

	// init the angle of left face
	int sizeFaceSL = m_index_sL.size();
	for (int i=0; i<sizeFaceSL; i++)
	{
		m_angle_sL_step1.push_back(0);
		m_angle_sL_step2.push_back(0);
	}

}

void cone::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	drawfaceSr(pShader);
	drawfaceSl(pShader);
	pShader->end();
}

void cone::unfold()
{
	unfoldSr();
	unfoldSl();
}

void cone::fold()
{
	/*foldSr();
	foldSl();*/
}

void cone::unfoldSl()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10;
		int sizeFaceSl = m_index_sL.size();
		double offsetAngle_l = offsetAngle/2;
		double offsetNewAngle_l = offsetNewAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		double offsetNewAngle_l_degree = offsetNewAngle_l * 180 / PI;
		for (int i=0; i<sizeFaceSl; i++)
		{
			m_angle_sL_step1[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * (sizeFaceSl - 1 - i) * offsetAngle_l_degree;
			m_angle_sL_step2[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * (sizeFaceSl - 1 - i) * offsetNewAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R));


		for (unsigned int i=1; i< m_index_sL.size(); i++)
		{
			
			temp3.SetRotationAxis(-m_angle_sL_step1[i],VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(-m_R * m_angle_sL_step1[i] * PI / 180 + 2 * m_R * sin(m_angle_sL_step1[i] * PI / 180), 0, 0));

			temp5.SetRotationAxis(-m_angle_sL_step2[i],VECTOR3D(0,1,0));
			temp6.SetTranslation(VECTOR3D(m_generatrix * m_angle_sL_step2[i] * PI / 180 - 2 * m_generatrix * sin(m_angle_sL_step2[i] * PI / 180), 0, 0));

			m_vertices[m_index_sL[i]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sL[i]];
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

void cone::unfoldSr()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10;
		int sizeFaceSr = m_index_sR.size();
		double offsetAngle_r = offsetAngle/2;
		double offsetNewAngle_r = offsetNewAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		double offsetNewAngle_r_degree = offsetNewAngle_r * 180 / PI;
		for (int i=0; i<sizeFaceSr; i++)
		{
			m_angle_sR_step1[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime *  i * offsetAngle_r_degree;
			m_angle_sR_step2[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime *  i * offsetNewAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R));
				
		for (unsigned int i=1; i< m_index_sR.size(); i++)
		{

			temp3.SetRotationAxis(m_angle_sR_step1[i],VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(m_R * m_angle_sR_step1[i] * PI / 180 - 2 * m_R * sin(m_angle_sR_step1[i] * PI / 180),0,0));

			temp5.SetRotationAxis(m_angle_sR_step2[i],VECTOR3D(0,1,0));
			temp6.SetTranslation(VECTOR3D(-m_generatrix * m_angle_sR_step2[i] * PI / 180 + 2 * m_generatrix * sin(m_angle_sR_step2[i] * PI / 180),0,0));

			m_vertices[m_index_sR[i]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sR[i]];
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

void cone::foldSl()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7;
		int sizeFaceSl = m_index_sL.size();
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFaceSl; i++)
		{
			m_angle_sL_step1[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * (sizeFaceSl - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R));
		temp7.SetTranslation(VECTOR3D(0,0,-m_R));

		for (int i=0; i< (int)m_index_sL.size(); i++)
		{
			temp3.SetRotationAxis(-(sizeFaceSl - 1 - i) * offsetAngle_l_degree,VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(-m_R * (sizeFaceSl - 1 - i) * offsetAngle_l_degree * PI / 180, 0, 0));

			temp5.SetTranslation(VECTOR3D(m_R * m_angle_sL_step1[i] * PI / 180, 0, 0));
			temp6.SetRotationAxis(m_angle_sL_step1[i],VECTOR3D(0,1,0));

			m_vertices[m_index_sL[i]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sL[i]];
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

void cone::foldSr()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7;
		int sizeFaceSr = m_index_sR.size();
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFaceSr; i++)
		{
			m_angle_sR_step1[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * i * offsetAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R));
		temp7.SetTranslation(VECTOR3D(0,0,-m_R));

		for (int i=1; i< (int)m_index_sR.size(); i++)
		{
			temp3.SetRotationAxis(i * offsetAngle_r_degree,VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(m_R * i * offsetAngle_r_degree * PI / 180, 0, 0));

			temp5.SetTranslation(VECTOR3D(-m_R * m_angle_sR_step1[i] * PI / 180, 0, 0));
			temp6.SetRotationAxis(-m_angle_sR_step1[i],VECTOR3D(0,1,0));

			m_vertices[m_index_sR[i]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sR[i]];
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

void cone::drawfaceSl(ShZshader *pShader)
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_sL.size() * sizeof(GL_UNSIGNED_INT), m_index_sL.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_sl);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_TRIANGLE_FAN,m_index_sL.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);

}

void cone::drawfaceSr(ShZshader *pShader)
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_sR.size() * sizeof(GL_UNSIGNED_INT), m_index_sR.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_sr);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_TRIANGLE_FAN,m_index_sR.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo2);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}
