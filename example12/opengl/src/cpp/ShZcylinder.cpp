#ifndef _PI_H
#define PI (3.1415926)
#endif

#include "ShZcylinder.h"

cylinder::cylinder()
{
	m_current = 0;
	m_start = clock();
	m_current = 0;
	m_totalTime = 10;
	m_angle_t = 0;
	m_angle_b = 0;
	//m_angle_s = 0;
	m_R = 0.2;
	m_H = 0.5;
	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;
	m_viewPosition = VECTOR3D(m_positionX - m_R, m_positionY, m_positionZ);
	m_lightPosition = VECTOR3D(m_positionX - 2 * m_R, m_positionY + 2 * m_H, m_positionZ + 2 * m_R);

	m_lightColor = VECTOR3D(1,1,1);
	m_objectColor = VECTOR3D(1,0,0);
	m_numberPoint = 50;
	offsetAngle = 2*PI/m_numberPoint;
	m_typeName = "cylinder";
	state = CLOSED;
	m_view.SetLookAt(m_R/4,m_H/2,m_R/2,0,0,0,0,1,0);
}

cylinder::~cylinder()
{
}

void cylinder::getPosition(GLdouble &positionX, GLdouble &positionY, GLdouble &positionZ)
{
	positionX = m_positionX;
	positionY = m_positionY;
	positionZ = m_positionZ;
}

void cylinder::setPosition(GLdouble positionX, GLdouble positionY, GLdouble positionZ)
{
	m_positionX = positionX;
	m_positionY = positionY;
	m_positionZ = positionZ;
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
	m_vertices_s.clear();
	m_vertices_b.clear();
	m_vertices_t.clear();
	m_vertices_temp.clear();
	m_normals_s.clear();
	m_normals_b.clear();
	m_normals_t.clear();
	m_index_top.clear();
	m_index_sider.clear();
	m_index_sidel.clear();
	m_index_compensation.clear();
	m_index_bottom.clear();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);
}

void cylinder::init()
{
	//init the vertice;
	// side face vertice
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices_s.push_back(VECTOR3D(m_positionX + m_R * cos(i*offsetAngle), m_positionY + m_H/2, m_positionZ + m_R * sin(i * offsetAngle)));
		m_normals_s.push_back(VECTOR3D(cos(i*offsetAngle), 0, sin(i * offsetAngle)));

		m_vertices_s.push_back(VECTOR3D(m_positionX + m_R * cos(i*offsetAngle), -m_H/2 + m_positionY, m_positionZ + m_R * sin(i * offsetAngle)));
		m_normals_s.push_back(VECTOR3D(cos(i*offsetAngle), 0, sin(i * offsetAngle)));
	}

	// top face vertice
	m_vertices_t.push_back(VECTOR3D(m_positionX, m_positionY + m_H/2, m_positionZ));
	m_normals_t.push_back(VECTOR3D(0, 1, 0));
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices_t.push_back(VECTOR3D(m_positionX + m_R * cos(i*offsetAngle), m_positionY + m_H/2, m_positionZ + m_R * sin(i * offsetAngle)));
		m_normals_t.push_back(VECTOR3D(0, 1, 0));
	}

	// bottom face vertice
	m_vertices_b.push_back(VECTOR3D(m_positionX, -m_H/2 + m_positionY, m_positionZ));
	m_normals_b.push_back(VECTOR3D(0, -1, 0));
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices_b.push_back(VECTOR3D(m_positionX + m_R * cos(i*offsetAngle), -m_H/2 + m_positionY, m_positionZ + m_R * sin(i * offsetAngle)));
		m_normals_b.push_back(VECTOR3D(0, -1, 0));
	}

	//m_vertices_temp
	m_vertices_temp = m_vertices_s;

	//index of top face and bottom face
	for (int i=0; i<m_numberPoint+1; i++)
	{
		m_index_top.push_back(i);
		m_index_bottom.push_back(i);
	}
	m_index_top.push_back(1);
	m_index_bottom.push_back(1);

	//index of right side face
	for (int i=0; i<m_numberPoint; i++)
	{
		m_index_sider.push_back(i);
	}

	m_index_compensation.push_back(m_numberPoint-2);
	m_index_compensation.push_back(m_numberPoint-1);
	m_index_compensation.push_back(m_numberPoint);
	m_index_compensation.push_back(m_numberPoint+1);

	//index of left side face
	for (int i=m_numberPoint; i<(m_numberPoint<<1); i++)
	{
		m_index_sidel.push_back(i);
	}
		m_index_sidel.push_back(0);
		m_index_sidel.push_back(1);

	// init the angle of side face
	int sizeFacel = m_index_sidel.size()>>1;
	for (int i=0; i<sizeFacel; i++)
	{
		m_angle_sl.push_back(0);
	}

	int sizeFacer = m_index_sider.size()>>1;
	for (int i=0; i<sizeFacer; i++)
	{
		m_angle_sr.push_back(0);
	}

}

void cylinder::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	drawfacet(pShader);
	drawfaceb(pShader);
	drawfacesl(pShader);
	drawfacesr(pShader);
	drawfaceCompensation(pShader);
	pShader->end();
}

void cylinder::unfold()
{
	unfoldt();
	unfoldb();
	unfoldsl();
	unfoldsr();
}

void cylinder::fold()
{
	foldsl();
	foldsr();
	foldt();
	foldb();	
}

void cylinder::unfoldsl()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		state = OPENING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		int sizeFacel = m_index_sidel.size()>>1;
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFacel; i++)
		{
			m_angle_sl[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * (sizeFacel - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,0,m_R));

		temp6.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		for (unsigned int i=0; i< m_index_sidel.size(); i+=2)
		{
			
			temp4.SetRotationAxis(-m_angle_sl[i>>1],VECTOR3D(0,1,0));
			temp5.SetTranslation(VECTOR3D(-m_R * 2 * m_angle_sl[i>>1] * PI / 180 + 2 * m_R * sin(m_angle_sl[i>>1] * PI / 180), 0, 0));

			m_vertices_s[m_index_sidel[i]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sidel[i]];
			m_vertices_s[m_index_sidel[i+1]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sidel[i+1]];
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
		glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals_s.size() * 3 * sizeof(GL_FLOAT),m_normals_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		
	}
}

void cylinder::unfoldsr()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		state = OPENING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		int sizeFacer = m_index_sider.size()>>1;
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFacer; i++)
		{
			m_angle_sr[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime *  i * offsetAngle_r_degree;
		}

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,0,m_R));

		temp6.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));
		
		for (unsigned int i=0; i< m_index_sider.size(); i+=2)
		{

			temp4.SetRotationAxis(m_angle_sr[i>>1],VECTOR3D(0,1,0));
			temp5.SetTranslation(VECTOR3D(m_R * 2 * m_angle_sr[i>>1] * PI / 180 - 2 * m_R * sin(m_angle_sr[i>>1] * PI / 180),0,0));

			m_vertices_s[m_index_sider[i]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sider[i]];
			m_vertices_s[m_index_sider[i+1]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sider[i+1]];
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
		glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals_s.size() * 3 * sizeof(GL_FLOAT),m_normals_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
}

void cylinder::unfoldt()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		state = OPENING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		m_model_top.LoadIdentity();

		m_angle_t = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,-m_H/2,m_R));
		temp4.SetRotationAxis(-m_angle_t,VECTOR3D(1,0,0));
		temp5.SetTranslation(VECTOR3D(0,m_H/2,0));

		temp6.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_top = temp6 * temp5 * temp4 * temp3 * temp2 * temp1;
	}
}

void cylinder::unfoldb()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		state = OPENING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		m_model_bottom.LoadIdentity();

		m_angle_b = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,m_H/2,m_R));
		temp4.SetRotationAxis(m_angle_b,VECTOR3D(1,0,0));
		temp5.SetTranslation(VECTOR3D(0,-m_H/2,0));

		temp6.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_bottom = temp6 * temp5 * temp4 * temp3 * temp2 * temp1;
	}
}

void cylinder::foldsl()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
		int sizeFacel = m_index_sidel.size()>>1;
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFacel; i++)
		{
			m_angle_sl[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * (sizeFacel - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,0,m_R));

		temp8.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		for (int i=0; i< (int)m_index_sidel.size(); i+=2)
		{
			temp4.SetRotationAxis(-(sizeFacel - 1 - i/2) * offsetAngle_l_degree,VECTOR3D(0,1,0));
			temp5.SetTranslation(VECTOR3D(-m_R * 2 * (sizeFacel - 1 - i/2) * offsetAngle_l_degree * PI / 180 + 2 * m_R * sin ((sizeFacel - 1 - i/2) * offsetAngle_l_degree * PI / 180), 0, 0));

			temp6.SetTranslation(VECTOR3D(m_R * 2 * m_angle_sl[i>>1] * PI / 180 - 2 * m_R * sin(m_angle_sl[i>>1] * PI / 180), 0, 0));
			temp7.SetRotationAxis(m_angle_sl[i>>1],VECTOR3D(0,1,0));

			m_vertices_s[m_index_sidel[i]] = temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sidel[i]];
			m_vertices_s[m_index_sidel[i+1]] = temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sidel[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);
		glDeleteBuffers(1,&m_nbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);
		glGenBuffers(1,&m_nbo);

		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals_s.size() * 3 * sizeof(GL_FLOAT),m_normals_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

	}
	else if ((m_current - m_start) > 2 * CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSED;
	}
}

void cylinder::foldsr()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
		int sizeFacer = m_index_sider.size()>>1;
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFacer; i++)
		{
			m_angle_sr[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * i * offsetAngle_r_degree;
		}

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,0,m_R));

		temp8.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		for (int i=0; i< (int)m_index_sider.size(); i+=2)
		{
			temp4.SetRotationAxis(i/2 * offsetAngle_r_degree,VECTOR3D(0,1,0));
			temp5.SetTranslation(VECTOR3D(m_R * i * offsetAngle_r_degree * PI / 180 - 2 * m_R * sin(i/2 * offsetAngle_r_degree * PI / 180), 0, 0));

			temp6.SetTranslation(VECTOR3D(-m_R * 2 * m_angle_sr[i>>1] * PI / 180 + 2 * m_R * sin(m_angle_sr[i>>1] * PI / 180), 0, 0));
			temp7.SetRotationAxis(-m_angle_sr[i>>1],VECTOR3D(0,1,0));

			m_vertices_s[m_index_sider[i]] = temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sider[i]];
			m_vertices_s[m_index_sider[i+1]] = temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sider[i+1]];
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
		glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals_s.size() * 3 * sizeof(GL_FLOAT),m_normals_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

	}
	else if ((m_current - m_start) > 2 * CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSED;
	}
}

void cylinder::foldt()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7;
		m_model_top.LoadIdentity();

		m_angle_t = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * 90;
		
		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,-m_H/2,m_R));
		temp4.SetRotationAxis(-90,VECTOR3D(1,0,0));
		temp5.SetRotationAxis(m_angle_t,VECTOR3D(1,0,0));
		temp6.SetTranslation(VECTOR3D(0,m_H/2,0));

		temp7.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_top = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1;
	}
	else if ((m_current - m_start) > 2 * CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSED;
	}
}

void cylinder::foldb()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSING;
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7;
		m_model_bottom.LoadIdentity();

		m_angle_b = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp3.SetTranslation(VECTOR3D(0,m_H/2,m_R));
		temp4.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp5.SetRotationAxis(-m_angle_b,VECTOR3D(1,0,0));
		temp6.SetTranslation(VECTOR3D(0,-m_H/2,0));

		temp7.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_bottom = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1;
	}
	else if ((m_current - m_start) > 2 * CLOCKS_PER_SEC * m_totalTime)
	{
		state = CLOSED;
	}
}

void cylinder::drawfacet(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);
	glGenBuffers(1,&m_nbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_t.size() * 3 * sizeof(GL_FLOAT),m_vertices_t.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals_t.size() * 3 * sizeof(GL_FLOAT),m_normals_t.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	GLuint ebo1;
	glGenBuffers(1,&ebo1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_top.size() * sizeof(GL_UNSIGNED_INT),m_index_top.data(),GL_STATIC_DRAW);


	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_top);


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

	glDrawElements(GL_TRIANGLE_FAN,m_index_top.size(),GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);

}

void cylinder::drawfaceb(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);
	glGenBuffers(1,&m_nbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_b.size() * 3 * sizeof(GL_FLOAT),m_vertices_b.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals_b.size() * 3 * sizeof(GL_FLOAT),m_normals_b.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	

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

	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_FAN,m_index_bottom.size(),GL_UNSIGNED_INT,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo2);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);

}

void cylinder::drawfacesl(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);
	glGenBuffers(1,&m_nbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals_s.size() * 3 * sizeof(GL_FLOAT),m_normals_s.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	GLuint ebo3;
	glGenBuffers(1,&ebo3);
	GLuint modelLocaiton, viewLocation, projectionLocation;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_sidel.size() * sizeof(GL_UNSIGNED_INT), m_index_sidel.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_sidel);

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

	glDrawElements(GL_TRIANGLE_STRIP,m_index_sidel.size(),GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo3);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);

}

void cylinder::drawfacesr(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);
	glGenBuffers(1,&m_nbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals_s.size() * 3 * sizeof(GL_FLOAT),m_normals_s.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	GLuint ebo4;
	glGenBuffers(1,&ebo4);
	GLuint modelLocaiton, viewLocation, projectionLocation;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_sider.size() * sizeof(GL_UNSIGNED_INT), m_index_sider.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_sider);

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

	glDrawElements(GL_TRIANGLE_STRIP,m_index_sider.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo4);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);
}

void cylinder::drawfaceCompensation(ShZshader *pShader)
{
	if (state == CLOSED)
	{
		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);
		glGenBuffers(1,&m_nbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals_s.size() * 3 * sizeof(GL_FLOAT),m_normals_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		GLuint ebo5;
		glGenBuffers(1,&ebo5);
		GLuint modelLocaiton, viewLocation, projectionLocation;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo5);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_compensation.size() * sizeof(GL_UNSIGNED_INT), m_index_compensation.data(), GL_STATIC_DRAW);

		modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
		glUniformMatrix4fv(modelLocaiton, 1, false, m_model_sider);

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

		glDrawElements(GL_TRIANGLE_STRIP,m_index_compensation.size(),GL_UNSIGNED_INT,0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		glDeleteBuffers(1,&ebo5);

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);
		glDeleteBuffers(1,&m_nbo);
	}
}

