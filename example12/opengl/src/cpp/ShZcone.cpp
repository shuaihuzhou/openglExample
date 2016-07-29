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
	m_R = 0.2;
	m_H = 0.8;
	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;
	m_viewPosition = VECTOR3D(m_positionX - m_R, m_positionY, m_positionZ);
	m_lightPosition = VECTOR3D(m_positionX - 2 * m_R, m_positionY + m_H, m_positionZ + 2 * m_R);

	m_lightColor = VECTOR3D(1,1,1);
	m_objectColor = VECTOR3D(1,0,0);
	m_generatrix = sqrt(m_R * m_R + m_H * m_H);
	m_unfoldedAngle = 2*PI*m_R/m_generatrix;
	cout<<m_unfoldedAngle * 180 / PI<<endl;
	m_numberPoint = 50;
	offsetAngle = 2*PI/m_numberPoint;
	offsetNewAngle = m_unfoldedAngle/m_numberPoint;
	m_typeName = "cone";
	state = CLOSED;
	m_view.SetLookAt(m_R/2,m_H/2,m_R,0,0,0,0,1,0);
}

cone::~cone()
{
}

void cone::getPosition(GLdouble &positionX, GLdouble &positionY, GLdouble &positionZ)
{
	positionX = m_positionX;
	positionY = m_positionY;
	positionZ = m_positionZ;
}

void cone::setPosition(GLdouble positionX, GLdouble positionY, GLdouble positionZ)
{
	m_positionX = positionX;
	m_positionY = positionY;
	m_positionZ = positionZ;
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
	m_unfoldedAngle = 2*PI*m_R/m_generatrix;
	offsetNewAngle = m_unfoldedAngle/m_numberPoint;
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
	m_normals.clear();
	m_index_compensation.clear();
	m_index_sL.clear();
	m_index_sR.clear();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);
}

void cone::init()
{
	//init the vertice;
	m_vertices.push_back(VECTOR3D(m_positionX, m_positionY + m_H/2, m_positionZ));
	m_normals.push_back(VECTOR3D(0,1,0));
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices.push_back(VECTOR3D(m_positionX + m_R * cos(i*offsetAngle), -m_H/2 + m_positionY, m_positionZ + m_R * sin(i * offsetAngle)));
		m_normals.push_back(VECTOR3D(cos(i*offsetAngle), 0, sin(i * offsetAngle)));
	}

	//m_vertices_temp
	m_vertices_temp = m_vertices;

	//index of right side face
	int middlPoint = (m_numberPoint>>1) + 1;
	for (int i=0; i<middlPoint; i++)
	{
		m_index_sR.push_back(i);
	}
	m_index_compensation.push_back(0);
	m_index_compensation.push_back(middlPoint-1);
	m_index_compensation.push_back(middlPoint);

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
	drawfaceCompensatin(pShader);
	pShader->end();
}

void cone::unfold()
{
	unfoldSr();
	unfoldSl();
}

void cone::fold()
{
	foldSr();
	foldSl();
}

void cone::unfoldSl()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		state = OPENING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10,temp11;
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

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));
		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,0,m_R));

		temp10.SetTranslation(VECTOR3D(0,0,-m_R));
		temp11.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		for (unsigned int i=1; i< m_index_sL.size(); i++)
		{
			
			temp4.SetRotationAxis(-m_angle_sL_step1[i],VECTOR3D(0,1,0));
			temp5.SetTranslation(VECTOR3D(-m_R * 2 * m_angle_sL_step1[i] * PI / 180 + m_R * 2 * sin(m_angle_sL_step1[i] * PI / 180), 0, 0));

			temp6.SetTranslation(VECTOR3D(m_generatrix * 2 * m_angle_sL_step2[i] * PI / 180 - m_generatrix * 2 * sin(m_angle_sL_step2[i] * PI / 180), 0 ,0));
			temp7.SetTranslation(VECTOR3D(0,m_H/2,0));
			temp8.SetRotationAxis(-m_angle_sL_step2[i],VECTOR3D(0,0,1));
			temp9.SetTranslation(VECTOR3D(0,-m_H/2,0));
			
			m_vertices[m_index_sL[i]] = temp11 * temp10 * temp9 * temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sL[i]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);
		glDeleteBuffers(1,&m_nbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);
		glGenBuffers(1,&m_nbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals.size() * 3 * sizeof(GL_FLOAT),m_normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		
	}
}

void cone::unfoldSr()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		state = OPENING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10,temp11;
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

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));
		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,0,m_R));

		temp10.SetTranslation(VECTOR3D(0,0,-m_R));
		temp11.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));
				
		for (unsigned int i=1; i< m_index_sR.size(); i++)
		{

			temp4.SetRotationAxis(m_angle_sR_step1[i],VECTOR3D(0,1,0));
			temp5.SetTranslation(VECTOR3D(m_R * 2 * m_angle_sR_step1[i] * PI / 180 - 2 * m_R * sin(m_angle_sR_step1[i] * PI / 180),0,0));

			temp6.SetTranslation(VECTOR3D(-m_generatrix * 2 * m_angle_sR_step2[i] * PI / 180 + m_generatrix * 2 * sin(m_angle_sR_step2[i] * PI / 180), 0, 0));
			temp7.SetTranslation(VECTOR3D(0,m_H/2,0));
			temp8.SetRotationAxis(m_angle_sR_step2[i],VECTOR3D(0,0,1));
			temp9.SetTranslation(VECTOR3D(0,-m_H/2,0));
			

			m_vertices[m_index_sR[i]] = temp11 * temp10 * temp9 * temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sR[i]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);
		glDeleteBuffers(1,&m_nbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);
		glGenBuffers(1,&m_nbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals.size() * 3 * sizeof(GL_FLOAT),m_normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
}

void cone::foldSl()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10,temp11,temp12,temp13,temp14,temp15;
		int sizeFaceSl = m_index_sL.size();
		double offsetAngle_l = offsetAngle/2;
		double offsetNewAngle_l = offsetNewAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		double offsetNewAngle_l_degree = offsetNewAngle_l * 180 / PI;
		for (int i=0; i<sizeFaceSl; i++)
		{
			m_angle_sL_step1[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * (sizeFaceSl - 1 - i) * offsetAngle_l_degree;
			m_angle_sL_step2[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * (sizeFaceSl - 1 - i) * offsetNewAngle_l_degree;
		}

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));
		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,0,m_R));

		temp14.SetTranslation(VECTOR3D(0,0,-m_R));
		temp15.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		for (int i=1; i< (int)m_index_sL.size(); i++)
		{

			temp4.SetRotationAxis(-(sizeFaceSl - 1 - i) * offsetAngle_l_degree,VECTOR3D(0,1,0));
			temp5.SetTranslation(VECTOR3D(-m_R * 2 * (sizeFaceSl - 1 - i) * offsetAngle_l_degree * PI / 180 + m_R * 2 * sin((sizeFaceSl - 1 - i) * offsetAngle_l_degree * PI / 180), 0, 0));

			temp6.SetTranslation(VECTOR3D(m_generatrix * 2 * (sizeFaceSl - 1 - i) * offsetNewAngle_l_degree * PI / 180 - m_generatrix * 2 * sin((sizeFaceSl - 1 - i) * offsetNewAngle_l_degree * PI / 180), 0, 0));
			temp7.SetTranslation(VECTOR3D(0,m_H/2,0));
			temp8.SetRotationAxis(-(sizeFaceSl - 1 - i) * offsetNewAngle_l_degree,VECTOR3D(0,0,1));
			
			temp9.SetRotationAxis(m_angle_sL_step2[i],VECTOR3D(0,0,1));
			temp10.SetTranslation(VECTOR3D(0,-m_H/2,0));
			temp11.SetTranslation(VECTOR3D(-m_generatrix * m_angle_sL_step2[i] * PI / 180 + m_generatrix * sin(m_angle_sL_step2[i] * PI / 180),0,0));
			
			temp12.SetTranslation(VECTOR3D(m_R * 2 * m_angle_sL_step1[i] * PI / 180 - m_R * 2 * sin(m_angle_sL_step1[i] * PI / 180),0,0));
			temp13.SetRotationAxis(m_angle_sL_step1[i],VECTOR3D(0,1,0));
			

			m_vertices[m_index_sL[i]] = temp15 * temp14 * temp13 * temp12 * temp11 * temp10 * temp9 * temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sL[i]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);
		glDeleteBuffers(1,&m_nbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);
		glGenBuffers(1,&m_nbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals.size() * 3 * sizeof(GL_FLOAT),m_normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

	}
	else if ((m_current - m_start) > 2 * CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSED;
	}
}

void cone::foldSr()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10,temp11,temp12,temp13,temp14,temp15;
		int sizeFaceSr = m_index_sR.size();
		double offsetAngle_r = offsetAngle/2;
		double offsetNewAngle_r = offsetNewAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		double offsetNewAngle_r_degree = offsetNewAngle_r * 180 / PI;
		for (int i=0; i<sizeFaceSr; i++)
		{
			m_angle_sR_step1[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime *  i * offsetAngle_r_degree;
			m_angle_sR_step2[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime *  i * offsetNewAngle_r_degree;
		}

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));
		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,0,m_R));

		temp14.SetTranslation(VECTOR3D(0,0,-m_R));
		temp15.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		for (int i=1; i< (int)m_index_sR.size(); i++)
		{

			temp4.SetRotationAxis(i * offsetAngle_r_degree,VECTOR3D(0,1,0));
			temp5.SetTranslation(VECTOR3D(m_R * 2 * i * offsetAngle_r_degree * PI / 180 - m_R * 2 * sin(i * offsetAngle_r_degree * PI / 180),0,0));

			temp6.SetTranslation(VECTOR3D(-m_generatrix * 2 * i * offsetNewAngle_r_degree * PI / 180 + m_generatrix * 2 * sin(i * offsetNewAngle_r_degree * PI / 180),0,0));
			temp7.SetTranslation(VECTOR3D(0,m_H/2,0));
			temp8.SetRotationAxis(i * offsetNewAngle_r_degree,VECTOR3D(0,0,1));
			
			temp9.SetRotationAxis(-m_angle_sR_step2[i],VECTOR3D(0,0,1));
			temp10.SetTranslation(VECTOR3D(0,-m_H/2,0));
			temp11.SetTranslation(VECTOR3D(m_generatrix * 2 * m_angle_sR_step2[i] * PI / 180 - m_generatrix * 2 * sin(m_angle_sR_step2[i] * PI / 180),0,0));
			

			temp12.SetTranslation(VECTOR3D(-m_R * 2 * m_angle_sR_step1[i] * PI / 180 + m_R * 2 * sin(m_angle_sR_step1[i] * PI / 180), 0, 0));
			temp13.SetRotationAxis(-m_angle_sR_step1[i],VECTOR3D(0,1,0));

			m_vertices[m_index_sR[i]] = temp15 * temp14 * temp13 * temp12 * temp11 * temp10 * temp9 * temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sR[i]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);
		glDeleteBuffers(1,&m_nbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);
		glGenBuffers(1,&m_nbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals.size() * 3 * sizeof(GL_FLOAT),m_normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
	else if ((m_current - m_start) > 2 * CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSED;
	}
}

void cone::drawfaceSl(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);
	glGenBuffers(1,&m_nbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * 3 * sizeof(GL_FLOAT),m_normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

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

	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_FAN,m_index_sL.size(),GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);

}

void cone::drawfaceSr(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);
	glGenBuffers(1,&m_nbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * 3 * sizeof(GL_FLOAT),m_normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

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

	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_FAN,m_index_sR.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);
}

void cone::drawfaceCompensatin(ShZshader *pShader)
{
	if (state == CLOSED)
	{
		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);
		glGenBuffers(1,&m_nbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals.size() * 3 * sizeof(GL_FLOAT),m_normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		GLuint ebo3;
		glGenBuffers(1,&ebo3);

		GLuint modelLocaiton, viewLocation, projectionLocation;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo3);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_compensation.size() * sizeof(GL_UNSIGNED_INT), m_index_compensation.data(), GL_STATIC_DRAW);

		modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
		glUniformMatrix4fv(modelLocaiton, 1, false, m_model_compensation);

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

		glDrawElements(GL_TRIANGLE_FAN,m_index_sR.size(),GL_UNSIGNED_INT,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		glDeleteBuffers(1,&ebo3);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);
		glDeleteBuffers(1,&m_nbo);
	}
}