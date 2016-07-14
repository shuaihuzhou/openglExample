#ifndef _PI_H
#define PI (3.1415926)
#endif

#include "ShZpipe.h"

pipe::pipe()
{
	m_current = 0;
	m_start = clock();
	m_current = 0;
	m_totalTime = 5;
	m_R_inner = 0.1;
	m_R_out = 0.2;
	m_H = 0.5;
	m_numberPoint = 50;
	offsetAngle = 2*PI/m_numberPoint;
	m_typeName = "pipe";
	m_view.SetLookAt(m_R_out/2,m_H/2,m_R_out,0,0,0,0,1,0);
}

pipe::~pipe()
{
}

void pipe::getRH(GLdouble &rinner, GLdouble &rout, GLdouble &h)
{
	rinner = m_R_inner;
	rout = m_R_out;
	h = m_H;
}

void pipe::setRH(GLdouble rinner, GLdouble rout, GLdouble h)
{
	m_R_inner = rinner;
	m_R_out = rout;
	m_H = h;
}

void pipe::getTypeName(string &p)
{
	p = m_typeName;
}

void pipe::setTypeName(const char* p)
{
	m_typeName = p;
}

void pipe::setTotalTime(double totalTime)
{
	m_totalTime = totalTime;
}

void pipe::begin()
{
	m_start = clock();
}

void pipe::end()
{
	m_start = 0;
	m_current = 0;
}

void pipe::clear()
{
	m_vertices_inner.clear();
	m_vertices_out.clear();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

void pipe::init()
{
	//init the vertice;
	// inner face vertice
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices_inner.push_back(VECTOR3D(m_R_inner * cos(i*offsetAngle), m_H/2, m_R_inner * sin(i * offsetAngle)));
		m_vertices_inner.push_back(VECTOR3D(m_R_inner * cos(i*offsetAngle), -m_H/2, m_R_inner * sin(i * offsetAngle)));  
	}

	// out face vertice
	for (int i=0; i<m_numberPoint; i++)
	{
		m_vertices_out.push_back(VECTOR3D(m_R_out * cos(i*offsetAngle), m_H/2, m_R_out * sin(i * offsetAngle)));
		m_vertices_out.push_back(VECTOR3D(m_R_out * cos(i*offsetAngle), -m_H/2, m_R_out * sin(i * offsetAngle)));  
	}

	//m_vertices_temp
	m_vertices_tempInner = m_vertices_inner;
	m_vertices_tempOut = m_vertices_out;

	//index of right side inner face
	for (int i=0; i<m_numberPoint; i++)
	{
		m_index_innerR.push_back(i);
	}
	m_index_innerR.push_back(m_numberPoint);
	m_index_innerR.push_back(m_numberPoint + 1);

	//index of left side inner face
	for (int i=m_numberPoint; i<(m_numberPoint<<1); i++)
	{
		m_index_innerL.push_back(i);
	}
		m_index_innerL.push_back(0);
		m_index_innerL.push_back(1);

	//index of right side out face
	for (int i=0; i<m_numberPoint; i++)
	{
		m_index_outR.push_back(i);
	}
	m_index_outR.push_back(m_numberPoint);
	m_index_outR.push_back(m_numberPoint + 1);

	//index of left side out face
	for (int i=m_numberPoint; i<(m_numberPoint<<1); i++)
	{
		m_index_outL.push_back(i);
	}
		m_index_outL.push_back(0);
		m_index_outL.push_back(1);

	// init the angle of right inner face
	int sizeFaceInnerR = m_index_innerR.size()>>1;
	for (int i=0; i<sizeFaceInnerR; i++)
	{
		m_angle_innerR.push_back(0);
	}

	// init the angle of left inner face
	int sizeFaceInnerL = m_index_innerL.size()>>1;
	for (int i=0; i<sizeFaceInnerL; i++)
	{
		m_angle_innerL.push_back(0);
	}

	// init the angle of right out face
	int sizeFaceOutR = m_index_outR.size()>>1;
	for (int i=0; i<sizeFaceOutR; i++)
	{
		m_angle_outR.push_back(0);
	}

	// init the angle of left out face
	int sizeFaceOutL = m_index_outL.size()>>1;
	for (int i=0; i<sizeFaceOutL; i++)
	{
		m_angle_outL.push_back(0);
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

void pipe::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	drawfaceInnerR(pShader);
	drawfaceInnerL(pShader);
	drawfaceOutR(pShader);
	drawfaceOutL(pShader);
	pShader->end();
}

void pipe::unfold()
{
	unfoldInnerR();
	unfoldInnerL();
	unfoldOutR();
	unfoldOutL();
}

void pipe::fold()
{
	foldInnerR();
	foldInnerL();
	foldOutR();
	foldOutL();	
}

void pipe::unfoldInnerL()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		int sizeFaceInnerL = m_index_innerL.size()>>1;
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFaceInnerL; i++)
		{
			m_angle_innerL[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * (sizeFaceInnerL - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R_inner));
		temp5.SetTranslation(VECTOR3D(0,0,-m_R_inner));

		for (unsigned int i=0; i< m_index_innerL.size(); i+=2)
		{
			
			temp3.SetRotationAxis(-m_angle_innerL[i>>1],VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(-m_R_inner * m_angle_innerL[i>>1] * PI / 180, 0, 0));

			m_vertices_inner[m_index_innerL[i]] = temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempInner[m_index_innerL[i]];
			m_vertices_inner[m_index_innerL[i+1]] = temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempInner[m_index_innerL[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_inner.size() * 3 * sizeof(GL_FLOAT),m_vertices_inner.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);

		
	}
}

void pipe::unfoldInnerR()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		int sizeFaceInnerR = m_index_innerR.size()>>1;
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFaceInnerR; i++)
		{
			m_angle_innerR[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime *  i * offsetAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R_inner));
		temp5.SetTranslation(VECTOR3D(0,0,-m_R_inner));
		
		for (unsigned int i=0; i< m_index_innerR.size(); i+=2)
		{

			temp3.SetRotationAxis(m_angle_innerR[i>>1],VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(m_R_inner *  m_angle_innerR[i>>1] * PI / 180,0,0));

			m_vertices_inner[m_index_innerR[i]] = temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempInner[m_index_innerR[i]];
			m_vertices_inner[m_index_innerR[i+1]] = temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempInner[m_index_innerR[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_inner.size() * 3 * sizeof(GL_FLOAT),m_vertices_inner.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);
	}
}

void pipe::unfoldOutL()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		int sizeFaceOutL = m_index_outL.size()>>1;
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFaceOutL; i++)
		{
			m_angle_outL[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * (sizeFaceOutL - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R_out));
		temp5.SetTranslation(VECTOR3D(0,0,-m_R_out));

		for (unsigned int i=0; i< m_index_outL.size(); i+=2)
		{

			temp3.SetRotationAxis(-m_angle_outL[i>>1],VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(-m_R_out * m_angle_outL[i>>1] * PI / 180, 0, 0));

			m_vertices_out[m_index_outL[i]] = temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempOut[m_index_outL[i]];
			m_vertices_out[m_index_outL[i+1]] = temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempOut[m_index_outL[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_out.size() * 3 * sizeof(GL_FLOAT),m_vertices_out.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);


	}
}

void pipe::unfoldOutR()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		int sizeFaceOutR = m_index_outR.size()>>1;
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFaceOutR; i++)
		{
			m_angle_outR[i] = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime *  i * offsetAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R_out));
		temp5.SetTranslation(VECTOR3D(0,0,-m_R_out));

		for (unsigned int i=0; i< m_index_innerR.size(); i+=2)
		{

			temp3.SetRotationAxis(m_angle_outR[i>>1],VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(m_R_out *  m_angle_outR[i>>1] * PI / 180,0,0));

			m_vertices_out[m_index_outR[i]] = temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempOut[m_index_outR[i]];
			m_vertices_out[m_index_outR[i+1]] = temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempOut[m_index_outR[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_out.size() * 3 * sizeof(GL_FLOAT),m_vertices_out.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);
	}
}

void pipe::foldInnerL()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7;
		int sizeFaceInnerL = m_index_innerL.size()>>1;
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFaceInnerL; i++)
		{
			m_angle_innerL[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * (sizeFaceInnerL - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R_inner));
		temp7.SetTranslation(VECTOR3D(0,0,-m_R_inner));

		for (int i=0; i< (int)m_index_innerL.size(); i+=2)
		{
			temp3.SetRotationAxis(-(sizeFaceInnerL - 1 - i/2) * offsetAngle_l_degree,VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(-m_R_inner * (sizeFaceInnerL - 1 - i/2) * offsetAngle_l_degree * PI / 180, 0, 0));

			temp5.SetTranslation(VECTOR3D(m_R_inner * m_angle_innerL[i>>1] * PI / 180, 0, 0));
			temp6.SetRotationAxis(m_angle_innerL[i>>1],VECTOR3D(0,1,0));

			m_vertices_inner[m_index_innerL[i]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempInner[m_index_innerL[i]];
			m_vertices_inner[m_index_innerL[i+1]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempInner[m_index_innerL[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_inner.size() * 3 * sizeof(GL_FLOAT),m_vertices_inner.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);


	}
}

void pipe::foldInnerR()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7;
		int sizeFaceInnerR = m_index_innerR.size()>>1;
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFaceInnerR; i++)
		{
			m_angle_innerR[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * i * offsetAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R_inner));
		temp7.SetTranslation(VECTOR3D(0,0,-m_R_inner));

		for (int i=0; i< (int)m_index_innerR.size(); i+=2)
		{
			temp3.SetRotationAxis(i/2 * offsetAngle_r_degree,VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(m_R_inner * i/2 * offsetAngle_r_degree * PI / 180, 0, 0));

			temp5.SetTranslation(VECTOR3D(-m_R_inner * m_angle_innerR[i>>1] * PI / 180, 0, 0));
			temp6.SetRotationAxis(-m_angle_innerR[i>>1],VECTOR3D(0,1,0));

			m_vertices_inner[m_index_innerR[i]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempInner[m_index_innerR[i]];
			m_vertices_inner[m_index_innerR[i+1]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempInner[m_index_innerR[i+1]];
		}



		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_inner.size() * 3 * sizeof(GL_FLOAT),m_vertices_inner.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);

	}
}

void pipe::foldOutL()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7;
		int sizeFaceOutL = m_index_outL.size()>>1;
		double offsetAngle_l = offsetAngle/2;
		double offsetAngle_l_degree = offsetAngle_l * 180 / PI;
		for (int i=0; i<sizeFaceOutL; i++)
		{
			m_angle_outL[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * (sizeFaceOutL - 1 - i) * offsetAngle_l_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R_out));
		temp7.SetTranslation(VECTOR3D(0,0,-m_R_out));

		for (int i=0; i< (int)m_index_outL.size(); i+=2)
		{
			temp3.SetRotationAxis(-(sizeFaceOutL - 1 - i/2) * offsetAngle_l_degree,VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(-m_R_out * (sizeFaceOutL - 1 - i/2) * offsetAngle_l_degree * PI / 180, 0, 0));

			temp5.SetTranslation(VECTOR3D(m_R_out * m_angle_outL[i>>1] * PI / 180, 0, 0));
			temp6.SetRotationAxis(m_angle_outL[i>>1],VECTOR3D(0,1,0));

			m_vertices_out[m_index_outL[i]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempOut[m_index_outL[i]];
			m_vertices_out[m_index_outL[i+1]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempOut[m_index_outL[i+1]];
		}

		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_out.size() * 3 * sizeof(GL_FLOAT),m_vertices_out.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);


	}
}

void pipe::foldOutR()
{
	m_current = clock();
	if ((m_current - m_start) < 2 * CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7;
		int sizeFaceOutR = m_index_outR.size()>>1;
		double offsetAngle_r = offsetAngle/2;
		double offsetAngle_r_degree = offsetAngle_r * 180 / PI;
		for (int i=0; i<sizeFaceOutR; i++)
		{
			m_angle_outR[i] = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime))/CLOCKS_PER_SEC/m_totalTime * i * offsetAngle_r_degree;
		}

		temp1.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2.SetTranslation(VECTOR3D(0,0,m_R_out));
		temp7.SetTranslation(VECTOR3D(0,0,-m_R_out));

		for (int i=0; i< (int)m_index_outR.size(); i+=2)
		{
			temp3.SetRotationAxis(i/2 * offsetAngle_r_degree,VECTOR3D(0,1,0));
			temp4.SetTranslation(VECTOR3D(m_R_out * i/2 * offsetAngle_r_degree * PI / 180, 0, 0));

			temp5.SetTranslation(VECTOR3D(-m_R_out * m_angle_outR[i>>1] * PI / 180, 0, 0));
			temp6.SetRotationAxis(-m_angle_outR[i>>1],VECTOR3D(0,1,0));

			m_vertices_out[m_index_outR[i]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempOut[m_index_outR[i]];
			m_vertices_out[m_index_outR[i+1]] = temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1 * m_vertices_tempOut[m_index_outR[i+1]];
		}



		glBindVertexArray(0);
		glDeleteVertexArrays(1,&m_vao);
		glDeleteBuffers(1,&m_vbo);

		glGenVertexArrays(1,&m_vao);
		glGenBuffers(1,&m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices_out.size() * 3 * sizeof(GL_FLOAT),m_vertices_out.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,0);

	}
}

void pipe::drawfaceOutL(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_out.size() * 3 * sizeof(GL_FLOAT),m_vertices_out.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	GLuint ebo1;
	glGenBuffers(1,&ebo1);
	GLuint modelLocaiton, viewLocation, projectionLocation;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_outL.size() * sizeof(GL_UNSIGNED_INT), m_index_outL.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_outL);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_LINES,m_index_outL.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);

}

void pipe::drawfaceOutR(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_out.size() * 3 * sizeof(GL_FLOAT),m_vertices_out.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	GLuint ebo2;
	glGenBuffers(1,&ebo2);
	GLuint modelLocaiton, viewLocation, projectionLocation;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_outR.size() * sizeof(GL_UNSIGNED_INT), m_index_outR.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_outR);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_LINES,m_index_outR.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo2);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}


void pipe::drawfaceInnerL(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_inner.size() * 3 * sizeof(GL_FLOAT),m_vertices_inner.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	GLuint ebo3;
	glGenBuffers(1,&ebo3);
	GLuint modelLocaiton, viewLocation, projectionLocation;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_innerL.size() * sizeof(GL_UNSIGNED_INT), m_index_innerL.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_innerL);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_LINES,m_index_innerL.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo3);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);

}

void pipe::drawfaceInnerR(ShZshader *pShader)
{
	glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices_inner.size() * 3 * sizeof(GL_FLOAT),m_vertices_inner.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	GLuint ebo4;
	glGenBuffers(1,&ebo4);
	GLuint modelLocaiton, viewLocation, projectionLocation;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_index_innerR.size() * sizeof(GL_UNSIGNED_INT), m_index_innerR.data(), GL_STATIC_DRAW);

	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_innerR);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_LINES,m_index_innerR.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo4);

	glBindVertexArray(0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

