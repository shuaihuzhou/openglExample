#include "ShZcube.h"


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
	m_totalTime = 3;
	m_anglel = 0;
	m_angler = 0;
	m_anglef = 0;
	m_angleb = 0;
	m_angleu = 0;
	m_angled = 0;
	m_L = 0.2;
	m_H = 0.3;
	m_W = 0.5;
	m_typeName = "cube";
	m_view.SetLookAt(m_L/2,m_H/2,m_W/2,-m_L/2,-m_H/2,-m_W/2,0,1,0);
}


void cube::getLWH(GLdouble &l,GLdouble &h, GLdouble &w)
{
	l = this->m_L;
	h = this->m_H;
	w = this->m_W;
}

void cube::setLWH(GLdouble l, GLdouble h, GLdouble w)
{
	this->m_L = l;
	this->m_H = h;
	this->m_W = w;
}

void cube::getTypeName(string &p)
{
	p = m_typeName;
}

void cube::setTypeName(const char* p)
{
	m_typeName = p;
}

void cube::setTotalTime(double totalTime)
{
	m_totalTime = totalTime;
}

void cube::clear()
{
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
}

void cube::begin()
{
	m_start = clock();
}

void cube::end()
{
	m_start = 0;
	m_current = 0;
}

void cube::init()
{

	//init the vertices;
	m_vertices.push_back(VECTOR3D(-m_L/2, -m_H/2, -m_W/2)); //vertex 0
	m_vertices.push_back(VECTOR3D(-m_L/2, -m_H/2, m_W/2)); //vertex 1
	m_vertices.push_back(VECTOR3D(-m_L/2, m_H/2, m_W/2)); //vertex 2
	m_vertices.push_back(VECTOR3D(-m_L/2, m_H/2, -m_W/2)); //vertex 3
	m_vertices.push_back(VECTOR3D(m_L/2, -m_H/2, -m_W/2)); //vertex 4
	m_vertices.push_back(VECTOR3D(m_L/2, -m_H/2, m_W/2)); //vertex 5
	m_vertices.push_back(VECTOR3D(m_L/2, m_H/2, m_W/2)); //vertex 6
	m_vertices.push_back(VECTOR3D(m_L/2, m_H/2, -m_W/2)); //vertex 7


	//init VAO VBO
	//glGenVertexArrays(1,&m_vao);
	glGenBuffers(1,&m_vbo);

	//glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GL_FLOAT),m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//glDrawArrays(GL_TRIANGLE_FAN,0,8);

	/*glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);*/

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	//glBindVertexArray(0);
}

void cube::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	//glBindVertexArray(m_vao);
	drawfacel(pShader);
	drawfacer(pShader);
	drawfacef(pShader);
	drawfaceb(pShader);
	drawfaceu(pShader);
	drawfaced(pShader);
	pShader->end();
}

void cube::unfold()
{
	unfoldl();
	unfoldr();
	unfoldf();
	unfoldb();
	unfoldu();
	unfoldd();
}

void cube::fold()
{
	foldl();
	foldr();
	foldf();
	foldb();
	foldu();
	foldd();
}

void cube::unfoldl()
{
	
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2;
		m_model_L.LoadIdentity();

		m_anglel = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;
		
		m_model_L.SetTranslation(VECTOR3D(m_L/2,0,-m_W/2));
		temp1 = m_model_L;
		m_model_L.SetRotationAxis(m_anglel,VECTOR3D(0,1,0));
		temp2 = m_model_L;
		m_model_L.SetTranslation(VECTOR3D(-m_L/2,0,m_W/2));
		m_model_L = m_model_L * temp2 * temp1;
		
		//glutPostRedisplay();
	}

}

void cube::unfoldr()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2;
		m_model_R.LoadIdentity();

		m_angler = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_R.SetTranslation(VECTOR3D(-m_L/2,0,-m_W/2));
		temp1 = m_model_R;
		m_model_R.SetRotationAxis(-m_anglel,VECTOR3D(0,1,0));
		temp2 = m_model_R;
		m_model_R.SetTranslation(VECTOR3D(m_L/2,0,m_W/2));
		m_model_R = m_model_R * temp2 * temp1;
		
		//glutPostRedisplay();
	}

}

void cube::unfoldf()
{

}

void cube::unfoldb()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 2 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime)
	{
		ShZMat4 temp1,temp2;
		m_model_B.LoadIdentity();
		
		m_angleb = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime) )/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_B.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		temp1 = m_model_B;
		m_model_B.SetRotationAxis(m_angleb,VECTOR3D(1,0,0));
		temp2 = m_model_B;
		m_model_B.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		m_model_B = m_model_B * temp2 * temp1;

		//glutPostRedisplay();
	}

	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 3 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 2)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		m_model_B.LoadIdentity();
		
		m_angleb = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 2) )/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_B.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		temp1 = m_model_B;
		m_model_B.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp2 = m_model_B;

		m_model_B.SetTranslation(VECTOR3D(0,0,-m_W));
		temp3 = m_model_B;
		m_model_B.SetRotationAxis(m_angleb,VECTOR3D(1,0,0));
		temp4 = m_model_B;

		m_model_B.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		temp5 = m_model_B;
		m_model_B.SetTranslation(VECTOR3D(0,0,m_W));

		m_model_B = m_model_B * temp5 * temp4 * temp3 * temp2 * temp1;


		//glutPostRedisplay();
	}

}

void cube::unfoldu()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 3 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 2)
	{
		ShZMat4 temp1,temp2;
		m_model_U.LoadIdentity();

		m_angleu = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 2))/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_U.SetTranslation(VECTOR3D(0,-m_H/2,-m_W/2));
		temp1 = m_model_U;
		m_model_U.SetRotationAxis(m_angleu,VECTOR3D(1,0,0));
		temp2 = m_model_U;
		m_model_U.SetTranslation(VECTOR3D(0,m_H/2,m_W/2));
		m_model_U = m_model_U * temp2 * temp1;

		//glutPostRedisplay();
	}
}

void cube::unfoldd()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 3 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 2)
	{
		ShZMat4 temp1,temp2;
		m_model_D.LoadIdentity();

		m_angled = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 2))/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_D.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		temp1 = m_model_D;
		m_model_D.SetRotationAxis(-m_angled,VECTOR3D(1,0,0));
		temp2 = m_model_D;
		m_model_D.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		m_model_D = m_model_D * temp2 * temp1;

		//glutPostRedisplay();
	}
}

void cube::foldl()
{

	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 6 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 5)
	{
		ShZMat4 temp1,temp2,temp3;
		m_model_L.LoadIdentity();

		m_anglel = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 5))/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_L.SetTranslation(VECTOR3D(m_L/2,0,-m_W/2));
		temp1 = m_model_L;
		m_model_L.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp2 = m_model_L;
		m_model_L.SetRotationAxis(-m_anglel,VECTOR3D(0,1,0));
		temp3 = m_model_L;
		m_model_L.SetTranslation(VECTOR3D(-m_L/2,0,m_W/2));
		m_model_L = m_model_L * temp3 * temp2 * temp1;

		//glutPostRedisplay();
	}

}

void cube::foldr()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 6 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 5)
	{
		ShZMat4 temp1,temp2,temp3;
		m_model_R.LoadIdentity();

		m_angler = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 5))/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_R.SetTranslation(VECTOR3D(-m_L/2,0,-m_W/2));
		temp1 = m_model_R;
		m_model_R.SetRotationAxis(-90,VECTOR3D(0,1,0));
		temp2 = m_model_R;
		m_model_R.SetRotationAxis(m_anglel,VECTOR3D(0,1,0));
		temp3 = m_model_R;
		m_model_R.SetTranslation(VECTOR3D(m_L/2,0,m_W/2));
		m_model_R = m_model_R * temp3 * temp2 * temp1;

		//glutPostRedisplay();
	}

}

void cube::foldf()
{

}

void cube::foldb()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 5 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 4)
	{
		ShZMat4 temp1,temp2,temp3;
		m_model_B.LoadIdentity();

		m_angleb = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 4) )/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_B.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		temp1 = m_model_B;
		m_model_B.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp2 = m_model_B;
		m_model_B.SetRotationAxis(-m_angleb,VECTOR3D(1,0,0));
		temp3 = m_model_B;
		m_model_B.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		m_model_B = m_model_B * temp3 * temp2 * temp1;

		//glutPostRedisplay();
	}

	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 4 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 3)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		m_model_B.LoadIdentity();

		m_angleb = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 3) )/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_B.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		temp1 = m_model_B;
		m_model_B.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp2 = m_model_B;

		m_model_B.SetTranslation(VECTOR3D(0,0,-m_W));
		temp3 = m_model_B;
		m_model_B.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp4 = m_model_B;
		m_model_B.SetRotationAxis(-m_angleb,VECTOR3D(1,0,0));
		temp5 = m_model_B;

		m_model_B.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		temp6 = m_model_B;
		m_model_B.SetTranslation(VECTOR3D(0,0,m_W));

		m_model_B = m_model_B * temp6 * temp5 * temp4 * temp3 * temp2 * temp1;


		//glutPostRedisplay();
	}

}

void cube::foldu()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 4 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 3)
	{
		ShZMat4 temp1,temp2,temp3;
		m_model_U.LoadIdentity();

		m_angleu = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 3))/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_U.SetTranslation(VECTOR3D(0,-m_H/2,-m_W/2));
		temp1 = m_model_U;
		m_model_U.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp2 = m_model_U;
		m_model_U.SetRotationAxis(-m_angleu,VECTOR3D(1,0,0));
		temp3 = m_model_U;
		m_model_U.SetTranslation(VECTOR3D(0,m_H/2,m_W/2));
		m_model_U = m_model_U * temp3 * temp2 * temp1;

		//glutPostRedisplay();
	}
}

void cube::foldd()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 4 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 3)
	{
		ShZMat4 temp1,temp2,temp3;
		m_model_D.LoadIdentity();

		m_angled = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 3))/CLOCKS_PER_SEC/m_totalTime * 90;

		m_model_D.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		temp1 = m_model_D;
		m_model_D.SetRotationAxis(-90,VECTOR3D(1,0,0));
		temp2 = m_model_D;
		m_model_D.SetRotationAxis(m_angled,VECTOR3D(1,0,0));
		temp3 = m_model_D;
		m_model_D.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		m_model_D = m_model_D * temp3 * temp2 * temp1;

		//glutPostRedisplay();
	}
}

void cube::drawfacel(ShZshader *pShader)
{
	GLuint ebo1;
	glGenBuffers(1,&ebo1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index1),index1,GL_STATIC_DRAW);


	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_L);

	
	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&ebo1);

}

void cube::drawfaceb(ShZshader *pShader)
{
	GLuint ebo2;
	glGenBuffers(1,&ebo2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index2),index2,GL_STATIC_DRAW);

	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_B);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);


	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo2);

}

void cube::drawfacer(ShZshader *pShader)
{
	GLuint ebo3;
	glGenBuffers(1,&ebo3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index3),index3,GL_STATIC_DRAW);


	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_R);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);

	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo3);

}

void cube::drawfacef(ShZshader *pShader)
{
	GLuint ebo4;
	glGenBuffers(1,&ebo4);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index4),index4,GL_STATIC_DRAW);


	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_F);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);


	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo4);

}

void cube::drawfaceu(ShZshader *pShader)
{
	GLuint ebo5;
	glGenBuffers(1,&ebo5);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index5),index5,GL_STATIC_DRAW);


	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_U);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);


	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo5);

}

void cube::drawfaced(ShZshader *pShader)
{
	GLuint ebo6;
	glGenBuffers(1,&ebo6);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index6),index6,GL_STATIC_DRAW);


	GLuint modelLocaiton, viewLocation, projectionLocation;
	modelLocaiton = glGetUniformLocation(pShader->programShader,"model");
	glUniformMatrix4fv(modelLocaiton, 1, false, m_model_D);

	viewLocation = glGetUniformLocation(pShader->programShader,"view");
	glUniformMatrix4fv(viewLocation, 1, false, m_view);

	projectionLocation = glGetUniformLocation(pShader->programShader, "projection");
	glUniformMatrix4fv(projectionLocation, 1, false, m_projection);


	glDrawElements(GL_LINES,8,GL_UNSIGNED_BYTE,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo6);

}