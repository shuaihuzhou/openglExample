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
	m_numberPoint = 50;
	offsetAngle = 2*PI/m_numberPoint;
	m_typeName = "cylinder";
	m_view.SetLookAt(m_R/2,m_H/2,m_R,0,0,0,0,1,0);
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
	m_vertices_s.clear();
	m_vertices_b.clear();
	m_vertices_t.clear();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

void cylinder::init()
{
	//init the vertice;
	// side face vertice
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices_s.push_back(VECTOR3D(m_R * cos(i*offsetAngle), m_H/2, m_R * sin(i * offsetAngle)));
		m_vertices_s.push_back(VECTOR3D(m_R * cos(i*offsetAngle), -m_H/2, m_R * sin(i * offsetAngle)));  
	}

	// top face vertice
	m_vertices_t.push_back(VECTOR3D(0, m_H/2, 0));
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices_t.push_back(VECTOR3D(m_R * cos(i*offsetAngle), m_H/2, m_R * sin(i * offsetAngle)));
	}

	// bottom face vertice
	m_vertices_b.push_back(VECTOR3D(0, -m_H/2, 0));
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices_b.push_back(VECTOR3D(m_R * cos(i*offsetAngle), -m_H/2, m_R * sin(i * offsetAngle)));
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
	m_index_sider.push_back(m_numberPoint);
	m_index_sider.push_back(m_numberPoint + 1);

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

	/*//init VAO VBO
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);*/

}

void cylinder::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	drawfacet(pShader);
	drawfaceb(pShader);
	drawfacesl(pShader);
	drawfacesr(pShader);
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
		ShZMat4 temp1,temp2,temp3,temp4;
		int sizeFacel = m_index_sidel.size()>>1;
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFacel; i++)
		{
			m_angle_sl[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * (sizeFacel - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R));

		for (unsigned int i=0; i< m_index_sidel.size(); i+=2)
		{
			
			temp3.SetRotationAxis(-m_angle_sl[i>>1],VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(-m_R * m_angle_sl[i>>1] * PI / 180, 0, 0));

			m_vertices_s[m_index_sidel[i]] = temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sidel[i]];
			m_vertices_s[m_index_sidel[i+1]] = temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sidel[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);

		
	}
}

void cylinder::unfoldsr()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4;
		int sizeFacer = m_index_sider.size()>>1;
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFacer; i++)
		{
			m_angle_sr[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime *  i * offsetAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R));
		
		for (unsigned int i=0; i< m_index_sider.size(); i+=2)
		{

			temp3.SetRotationAxis(m_angle_sr[i>>1],VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(m_R *  m_angle_sr[i>>1] * PI / 180,0,0));

			m_vertices_s[m_index_sider[i]] = temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sider[i]];
			m_vertices_s[m_index_sider[i+1]] = temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sider[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);
	}
}

void cylinder::unfoldt()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4;
		m_model_top.LoadIdentity();

		m_angle_t = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,-m_H/2,m_R));
		temp3.SetRotationAxis(-m_angle_t,VECTOR3D(1,0,0));
		temp4.SetTranslation(VECTOR3D(0,m_H/2,0));
		m_model_top =temp4 * temp3 * temp2 * temp1;
	}
}

void cylinder::unfoldb()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4;
		m_model_bottom.LoadIdentity();

		m_angle_b = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,m_H/2,m_R));
		temp3.SetRotationAxis(m_angle_b,VECTOR3D(1,0,0));
		temp4.SetTranslation(VECTOR3D(0,-m_H/2,0));
		m_model_bottom = temp4 * temp3 * temp2 * temp1;
	}
}

void cylinder::foldsl()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		int sizeFacel = m_index_sidel.size()>>1;
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFacel; i++)
		{
			m_angle_sl[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * (sizeFacel - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R));

		for (int i=0; i< (int)m_index_sidel.size(); i+=2)
		{
			temp3.SetRotationAxis(-(sizeFacel - 1 - i/2) * offsetAngle_l_degree,VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(-m_R * (sizeFacel - 1 - i/2) * offsetAngle_l_degree * PI / 180, 0, 0));

			temp5.SetTranslation(VECTOR3D(m_R * m_angle_sl[i>>1] * PI / 180, 0, 0));
			temp6.SetRotationAxis(m_angle_sl[i>>1],VECTOR3D(0,1,0));

			m_vertices_s[m_index_sidel[i]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sidel[i]];
			m_vertices_s[m_index_sidel[i+1]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sidel[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);


	}
}

void cylinder::foldsr()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		int sizeFacer = m_index_sider.size()>>1;
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFacer; i++)
		{
			m_angle_sr[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * i * offsetAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R));

		for (int i=0; i< (int)m_index_sider.size(); i+=2)
		{
			temp3.SetRotationAxis(i/2 * offsetAngle_r_degree,VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(m_R * i/2 * offsetAngle_r_degree * PI / 180, 0, 0));

			temp5.SetTranslation(VECTOR3D(-m_R * m_angle_sr[i>>1] * PI / 180, 0, 0));
			temp6.SetRotationAxis(-m_angle_sr[i>>1],VECTOR3D(0,1,0));

			m_vertices_s[m_index_sider[i]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sider[i]];
			m_vertices_s[m_index_sider[i+1]] = temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_temp[m_index_sider[i+1]];
		}



		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);


	}
}

void cylinder::foldt()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		m_model_top.LoadIdentity();

		m_angle_t = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * 90;
		

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,-m_H/2,m_R));
		temp3.SetRotationAxis(-90,VECTOR3D(1,0,0));
		temp4.SetRotationAxis(m_angle_t,VECTOR3D(1,0,0));
		temp5.SetTranslation(VECTOR3D(0,m_H/2,0));
		m_model_top =temp5 * temp4 * temp3 * temp2 * temp1;
	}
}

void cylinder::foldb()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		m_model_bottom.LoadIdentity();

		m_angle_b = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,m_H/2,m_R));
		temp3.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp4.SetRotationAxis(-m_angle_b,VECTOR3D(1,0,0));
		temp5.SetTranslation(VECTOR3D(0,-m_H/2,0));
		m_model_bottom =temp5 * temp4 * temp3 * temp2 * temp1;
	}
}

void cylinder::drawfacet(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_t.size() * 3 * sizeof(GL_FLOAT),m_vertices_t.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);

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

	glDrawElements(GL_TRIANGLE_FAN,m_index_top.size(),GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);

}

void cylinder::drawfaceb(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_b.size() * 3 * sizeof(GL_FLOAT),m_vertices_b.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);

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

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);

}

void cylinder::drawfacesl(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);

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

	glDrawElements(GL_TRIANGLE_STRIP,m_index_sidel.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo3);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);

}

void cylinder::drawfacesr(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_s.size() * 3 * sizeof(GL_FLOAT),m_vertices_s.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);

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

	glDrawElements(GL_TRIANGLE_STRIP,m_index_sider.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo4);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

