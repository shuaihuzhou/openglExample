#include "ShZcube.h"


GLubyte index1[]={
	0,1,3,2 //left
};
GLubyte index2[]={
	4,5,6,7 //back
};
GLubyte index3[]={
	8,9,11,10 //right
};
GLubyte index4[]={
	12,13,14,15 //front
};
GLubyte index5[]={
	16,17,18,19 //up
};
GLubyte index6[]={
	20,21,22,23 //down
};

cube::cube()
{
	m_current = 0;
	m_start = clock();
	m_current = 0;
	m_totalTime = 4;
	m_anglel = 0;
	m_angler = 0;
	m_anglef = 0;
	m_angleb = 0;
	m_angleu = 0;
	m_angled = 0;
	m_L = 0.5;
	m_H = 0.5;
	m_W = 0.5;
	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;
	m_viewPosition = VECTOR3D(m_positionX - 1, m_positionY, m_positionZ);
	m_lightPosition = VECTOR3D(m_positionX + 1, m_positionY + 1, m_positionZ + 1);

	m_lightColor = VECTOR3D(1,1,1);
	m_objectColor = VECTOR3D(1,0,0);
	m_typeName = "cube";
	m_view.SetLookAt(m_L/2,m_H/2,m_W/2,-m_L/2,-m_H/2,-m_W/2,0,1,0);
}

void cube::getPosition(GLdouble &x,GLdouble &y, GLdouble &z)
{
	x = this->m_positionX;
	y = this->m_positionY;
	z = this->m_positionZ;
}

void cube::setPosition(GLdouble x, GLdouble y, GLdouble z)
{
	this->m_positionX = x;
	this->m_positionY = y;
	this->m_positionZ = z;
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
	m_vertices.clear();
	m_normals.clear();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_nbo);
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
	//init the left face vertice
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, -m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 0 index 0
	m_normals.push_back(VECTOR3D(-1,0,0));
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, -m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 1  index 1
	m_normals.push_back(VECTOR3D(-1,0,0));
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 2   index 2
	m_normals.push_back(VECTOR3D(-1,0,0));
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 3  index 3
	m_normals.push_back(VECTOR3D(-1,0,0));

	//init the back face vertice
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, -m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 0 index 4
	m_normals.push_back(VECTOR3D(0,0,-1));
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 3  index 5
	m_normals.push_back(VECTOR3D(0,0,-1));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, -m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 4  index 6
	m_normals.push_back(VECTOR3D(0,0,-1));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 7   index 7
	m_normals.push_back(VECTOR3D(0,0,-1));

	//init the right face vertice
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, -m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 4  index 8
	m_normals.push_back(VECTOR3D(1,0,0));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, -m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 5   index 9
	m_normals.push_back(VECTOR3D(1,0,0));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 6    index 10
	m_normals.push_back(VECTOR3D(1,0,0));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 7   index 11
	m_normals.push_back(VECTOR3D(1,0,0));

	//init the front face vertice
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, -m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 1  index 12
	m_normals.push_back(VECTOR3D(0,0,1));
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 2   index 13
	m_normals.push_back(VECTOR3D(0,0,1));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, -m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 5   index 14
	m_normals.push_back(VECTOR3D(0,0,1));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 6    index 15
	m_normals.push_back(VECTOR3D(0,0,1));
	

	//init the up face vertice
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 2   index 16
	m_normals.push_back(VECTOR3D(0,1,0));
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 3  index 17
	m_normals.push_back(VECTOR3D(0,1,0));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 6    index 18
	m_normals.push_back(VECTOR3D(0,1,0));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 7   index 19
	m_normals.push_back(VECTOR3D(0,1,0));

	//init the down face vertice
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, -m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 0 index 20
	m_normals.push_back(VECTOR3D(0,-1,0));
	m_vertices.push_back(VECTOR3D(-m_L/2 + m_positionX, -m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 1  index 21
	m_normals.push_back(VECTOR3D(0,-1,0));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, -m_H/2 + m_positionY, -m_W/2 + m_positionZ)); //vertex 4  index 22
	m_normals.push_back(VECTOR3D(0,-1,0));
	m_vertices.push_back(VECTOR3D(m_L/2 + m_positionX, -m_H/2 + m_positionY, m_W/2 + m_positionZ)); //vertex 5   index 23
	m_normals.push_back(VECTOR3D(0,-1,0));


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

void cube::draw_shape(ShZshader *pShader)
{
	pShader->begin();
	glBindVertexArray(m_vao);
 	drawfacel(pShader);
 	drawfacer(pShader);
	drawfacef(pShader);
 	drawfaceb(pShader);
 	drawfaceu(pShader);
 	drawfaced(pShader);
	glBindVertexArray(0);
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
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		m_model_L.LoadIdentity();

		m_anglel = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;
		
		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));
		temp2.SetTranslation(VECTOR3D(m_L/2,0,-m_W/2));
		temp3.SetRotationAxis(m_anglel,VECTOR3D(0,1,0));
		temp4.SetTranslation(VECTOR3D(-m_L/2,0,m_W/2));
		temp5.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));
		m_model_L = temp5 * temp4 * temp3 * temp2 * temp1;
		
		//glutPostRedisplay();
	}

}

void cube::unfoldr()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime && (m_current - m_start) >= 0)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		m_model_R.LoadIdentity();

		m_angler = (double)(m_current - m_start)/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));
		temp2.SetTranslation(VECTOR3D(-m_L/2,0,-m_W/2));
		temp3.SetRotationAxis(-m_anglel,VECTOR3D(0,1,0));
		temp4.SetTranslation(VECTOR3D(m_L/2,0,m_W/2));
		temp5.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));
		m_model_R = temp5 * temp4 * temp3 * temp2 * temp1;
		
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
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		m_model_B.LoadIdentity();
		
		m_angleb = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime) )/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));
		temp2.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		temp3.SetRotationAxis(m_angleb,VECTOR3D(1,0,0));
		temp4.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		temp5.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));
		m_model_B = temp5* temp4 * temp3 * temp2 * temp1;

	}

	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 3 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 2)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
		m_model_B.LoadIdentity();
		
		m_angleb = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 2) )/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		temp3.SetRotationAxis(90,VECTOR3D(1,0,0));

		temp4.SetTranslation(VECTOR3D(0,0,-m_W));
		temp5.SetRotationAxis(m_angleb,VECTOR3D(1,0,0));

		temp6.SetTranslation(VECTOR3D(0,0,m_W));
		temp7.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		
		temp8.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_B = temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1;

	}

}

void cube::unfoldu()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 3 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 2)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		m_model_U.LoadIdentity();

		m_angleu = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 2))/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetTranslation(VECTOR3D(0,-m_H/2,-m_W/2));
		temp3.SetRotationAxis(m_angleu,VECTOR3D(1,0,0));
		temp4.SetTranslation(VECTOR3D(0,m_H/2,m_W/2));

		temp5.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));
		m_model_U = temp5 * temp4 * temp3 * temp2 * temp1;

	}
}

void cube::unfoldd()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 3 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 2)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5;
		m_model_D.LoadIdentity();

		m_angled = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 2))/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		temp3.SetRotationAxis(-m_angled,VECTOR3D(1,0,0));
		temp4.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));

		temp5.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_D = temp5 * temp4 * temp3 * temp2 * temp1;

	}
}

void cube::foldl()
{

	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 6 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 5)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		m_model_L.LoadIdentity();

		m_anglel = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 5))/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetTranslation(VECTOR3D(m_L/2,0,-m_W/2));
		temp3.SetRotationAxis(90,VECTOR3D(0,1,0));
		temp4.SetRotationAxis(-m_anglel,VECTOR3D(0,1,0));
		temp5.SetTranslation(VECTOR3D(-m_L/2,0,m_W/2));

		temp6.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_L = temp6 * temp5 * temp4 * temp3 * temp2 * temp1;

	}

}

void cube::foldr()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 6 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 5)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		m_model_R.LoadIdentity();

		m_angler = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 5))/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetTranslation(VECTOR3D(-m_L/2,0,-m_W/2));
		temp3.SetRotationAxis(-90,VECTOR3D(0,1,0));
		temp4.SetRotationAxis(m_anglel,VECTOR3D(0,1,0));
		temp5.SetTranslation(VECTOR3D(m_L/2,0,m_W/2));

		temp6.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_R = temp6 * temp5 * temp4 * temp3 * temp2 * temp1;

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
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		m_model_B.LoadIdentity();

		m_angleb = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 4) )/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		temp3.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp4.SetRotationAxis(-m_angleb,VECTOR3D(1,0,0));
		temp5.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));

		temp6.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_B = temp6 * temp5 * temp4 * temp3 * temp2 * temp1;

	}

	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 4 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 3)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
		m_model_B.LoadIdentity();

		m_angleb = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 3) )/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));
		temp3.SetRotationAxis(90,VECTOR3D(1,0,0));

		temp4.SetTranslation(VECTOR3D(0,0,-m_W));
		temp5.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp6.SetRotationAxis(-m_angleb,VECTOR3D(1,0,0));

		temp7.SetTranslation(VECTOR3D(0,0,m_W));
		temp8.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		
		temp9.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_B = temp9 * temp8 * temp7 * temp6 * temp5 * temp4 * temp3 * temp2 * temp1;

	}

}

void cube::foldu()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 4 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 3)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		m_model_U.LoadIdentity();

		m_angleu = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 3))/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetTranslation(VECTOR3D(0,-m_H/2,-m_W/2));
		temp3.SetRotationAxis(90,VECTOR3D(1,0,0));
		temp4.SetRotationAxis(-m_angleu,VECTOR3D(1,0,0));
		temp5.SetTranslation(VECTOR3D(0,m_H/2,m_W/2));

		temp6.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_U = temp6 * temp5 * temp4 * temp3 * temp2 * temp1;

	}
}

void cube::foldd()
{
	m_current = clock();
	if ((m_current - m_start) < CLOCKS_PER_SEC * m_totalTime * 4 && (m_current - m_start) > CLOCKS_PER_SEC * m_totalTime * 3)
	{
		ShZMat4 temp1,temp2,temp3,temp4,temp5,temp6;
		m_model_D.LoadIdentity();

		m_angled = (double)(m_current - (m_start + CLOCKS_PER_SEC * m_totalTime * 3))/CLOCKS_PER_SEC/m_totalTime * 90;

		temp1.SetTranslation(VECTOR3D(-m_positionX, -m_positionY, -m_positionZ));

		temp2.SetTranslation(VECTOR3D(0,m_H/2,-m_W/2));
		temp3.SetRotationAxis(-90,VECTOR3D(1,0,0));
		temp4.SetRotationAxis(m_angled,VECTOR3D(1,0,0));
		temp5.SetTranslation(VECTOR3D(0,-m_H/2,m_W/2));

		temp6.SetTranslation(VECTOR3D(m_positionX, m_positionY, m_positionZ));

		m_model_D = temp6 * temp5 * temp4 * temp3 * temp2 * temp1;

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

	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_BYTE,0);


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


	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_BYTE,0);


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

	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_BYTE,0);


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


	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_BYTE,0);


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


	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_BYTE,0);


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


	GLuint viewPosLoc,lightPosLoc,lightColorLoc,objecColorLoc;
	viewPosLoc = glGetUniformLocation(pShader->programShader,"viewPos");
	glUniform3f(viewPosLoc, m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	lightPosLoc = glGetUniformLocation(pShader->programShader,"lightPos");
	glUniform3f(lightPosLoc, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

	lightColorLoc = glGetUniformLocation(pShader->programShader,"lightColor");
	glUniform3f(lightColorLoc, m_lightColor.x, m_lightColor.y, m_lightColor.z);

	objecColorLoc = glGetUniformLocation(pShader->programShader,"objectColor");
	glUniform3f(objecColorLoc, m_objectColor.x, m_objectColor.y, m_objectColor.z);

	glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_BYTE,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDeleteBuffers(1,&ebo6);

}