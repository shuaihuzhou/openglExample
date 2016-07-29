#include "ShZshapeManager.h"


ShZshapeManager::ShZshapeManager()
{
}

ShZshapeManager::~ShZshapeManager()
{
}

vector<ShZdrawManager*> ShZshapeManager::getDrawManager()
{
	return m_drawManagers;
}

vector<ShZanimationManager*> ShZshapeManager::getAnimationManager()
{
	return m_animationManagers;
}

vector<ShZtimeManager*> ShZshapeManager::getTimeManager()
{
	return m_timeManagers;
}

void ShZshapeManager::create_shape(const char* content)
{
	if (content == "cube")
	{
		create_cube();
	}

	if (content == "cylinder")
	{
		create_cylinder();
	}

	if (content == "pipe")
	{
		create_pipe();
	}

	if (content == "cone")
	{
		create_cone();
	}

	if (content == "circle")
	{
		create_circle();
	}

	if (content == "ring")
	{
		create_ring();
	}

	if (content == "pyramid")
	{
		create_pyramid();
	}

	if (content == "triangle")
	{
		create_triangle();
	}

	if (content == "rectangle")
	{
		create_rectangle();
	}

	if (content == "polygon")
	{
		create_polygon();
	}

	if (content == "multigonalStar")
	{
		create_multigonalStar();
	}

}

void ShZshapeManager::create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r)
{
	if (content == "circle")
	{
		create_circle(positionX, positionY, positionZ, r);
	}

	if (content == "ring")
	{
		create_ring(positionX, positionY, positionZ, r);
	}

	if (content == "triangle")
	{
		create_triangle(positionX, positionY, positionZ, r);
	}

	if (content == "rectangle")
	{
		create_rectangle(positionX, positionY, positionZ, r);
	}

}

void ShZshapeManager::create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r, GLdouble h)
{
	if (content == "cylinder")
	{
		create_cylinder(positionX, positionY, positionZ, r, h);
	}

	if (content == "cone")
	{
		create_cone(positionX, positionY, positionZ, r, h);
	}

}

void ShZshapeManager::create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges_angles,  GLdouble r)
{
	if (content == "polygon")
	{
		create_polygon(positionX, positionY, positionZ, edges_angles, r);
	}

	if (content == "multigonalStar")
	{
		create_multigonalStar(positionX, positionY, positionZ, edges_angles, r);
	}

}

void ShZshapeManager::create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges, GLdouble h, GLdouble r)
{
	if (content == "pyramid")
	{
		create_pyramid(positionX, positionY, positionZ, edges, h, r);
	}
}

void ShZshapeManager::create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble l_rin, GLdouble h_rout, GLdouble w_h)
{
	if (content == "cube")
	{
		create_cube(positionX, positionY, positionZ, l_rin, h_rout, w_h);
	}

	if (content == "pipe")
	{
		create_pipe(positionX, positionY, positionZ, l_rin, h_rout, w_h);
	}
}

void ShZshapeManager::draw_shape(const char* content)
{
	if (content == "cube")
	{
		draw_cube();
	}

	if (content == "cylinder")
	{
		draw_cylinder();
	}

	if (content == "pipe")
	{
		draw_pipe();
	}

	if (content == "cone")
	{
		draw_cone();
	}

	if (content == "circle")
	{
		draw_circle();
	}

	if (content == "ring")
	{
		draw_ring();
	}

	if (content == "pyramid")
	{
		draw_pyramid();
	}

	if (content == "triangle")
	{
		draw_triangle();
	}

	if (content == "rectangle")
	{
		draw_rectangle();
	}

	if (content == "polygon")
	{
		draw_polygon();
	}

	if (content == "multigonalStar")
	{
		draw_multigonalStar();
	}
}

void ShZshapeManager::unfold_shape(const char* content)
{
	if (content == "cube")
	{
		unfold_cube();
	}

	if (content == "cylinder")
	{
		unfold_cylinder();
	}

	if (content == "pipe")
	{
		unfold_pipe();
	}

	if (content == "cone")
	{
		unfold_cone();
	}

	if (content == "circle")
	{
		unfold_circle();
	}

	if (content == "ring")
	{
		unfold_ring();
	}

	if (content == "pyramid")
	{
		unfold_pyramid();
	}

	if (content == "triangle")
	{
		unfold_triangle();
	}

	if (content == "rectangle")
	{
		unfold_rectangle();
	}

	if (content == "multigonalStar")
	{
		unfold_multigonalStar();
	}
}

void ShZshapeManager::fold_shape(const char* content)
{
	if (content == "cube")
	{
		fold_cube();
	}

	if (content == "cylinder")
	{
		fold_cylinder();
	}

	if (content == "pipe")
	{
		fold_pipe();
	}

	if (content == "cone")
	{
		fold_cone();
	}

	if (content == "circle")
	{
		fold_circle();
	}

	if (content == "ring")
	{
		fold_ring();
	}

	if (content == "pyramid")
	{
		fold_pyramid();
	}

	if (content == "triangle")
	{
		fold_triangle();
	}

	if (content == "rectangle")
	{
		fold_rectangle();
	}

	if (content == "polygon")
	{
		fold_polygon();
	}

	if (content == "multigonalStar")
	{
		fold_multigonalStar();
	}
}

void ShZshapeManager::begin(const char* content)
{
	if (content == "cube")
	{
		begin_cube();
	}

	if (content == "cylinder")
	{
		begin_cylinder();
	}

	if (content == "pipe")
	{
		begin_pipe();
	}

	if (content == "cone")
	{
		begin_cone();
	}

	if (content == "circle")
	{
		begin_circle();
	}

	if (content == "ring")
	{
		begin_ring();
	}

	if (content == "pyramid")
	{
		begin_pyramid();
	}

	if (content == "triangle")
	{
		begin_triangle();
	}

	if (content == "rectangle")
	{
		begin_rectangle();
	}

	if (content == "polygon")
	{
		begin_polygon();
	}

	if (content == "mutigonalStar")
	{
		begin_multigonalStar();
	}
}

void ShZshapeManager::end(const char* content)
{
	if (content == "cube")
	{
		end_cube();
	}

	if (content == "cylinder")
	{
		end_cylinder();
	}

	if (content == "pipe")
	{
		end_pipe();
	}

	if (content == "cone")
	{
		end_cone();
	}

	if (content == "circle")
	{
		end_circle();
	}

	if (content == "ring")
	{
		end_ring();
	}

	if (content == "pyramid")
	{
		end_pyramid();
	}

	if (content == "triangle")
	{
		end_triangle();
	}

	if (content == "rectangle")
	{
		end_rectangle();
	}

	if (content == "polygon")
	{
		end_polygon();
	}

	if (content == "multigonalStar")
	{
		end_multigonalStar();
	}
}

void ShZshapeManager::clear()
{
// 	int sizeDrawManagers;
// 	int sizeAnimationManagers;
// 	int sizeTimeManagers;
	

// 	sizeDrawManagers = m_drawManagers.size();
// 	sizeAnimationManagers = m_animationManagers.size();
// 	sizeTimeManagers = m_timeManagers.size();
	
	
// 	for (int i=0; i<sizeDrawManagers; i++)
// 	{
// 		delete m_drawManagers[i];
// 		m_drawManagers[i] = nullptr;
// 	}
// 
// 	for (int i=0; i<sizeAnimationManagers; i++)
// 	{
// 		delete m_animationManagers[i];
// 		m_animationManagers[i] = nullptr;
// 	}
// 	
// 	for (int i=0; i<sizeTimeManagers; i++)
// 	{
// 		delete m_timeManagers[i];
// 		m_timeManagers[i] = nullptr;
// 	}
	int sizeClearManagers;
	sizeClearManagers = m_clearManagers.size();

	for (int i=0; i<sizeClearManagers; i++)
	{
		m_clearManagers[i]->clear();
		delete m_clearManagers[i];
		m_clearManagers[i] = nullptr;
	}

	m_drawManagers.clear();
	m_animationManagers.clear();
	m_timeManagers.clear();
	m_clearManagers.clear();

}

void ShZshapeManager::create_cube()
{
	cube *cubeNew;
	cubeNew = new cube;
	cubeNew->init();
	m_drawManagers.push_back(cubeNew);
	m_animationManagers.push_back(cubeNew);
	m_timeManagers.push_back(cubeNew);
	m_clearManagers.push_back(cubeNew);
}

void ShZshapeManager::create_cube(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble l, GLdouble h, GLdouble w)
{
	if (positionX + l/2 >= 1 || positionX - l/2 <= -1 || positionZ + w/2 >= 1 ||  positionZ - w/2 <= -1 || positionY + h/2 >= 1 || positionY - h/2 <= -1)
	{
		cout<<"error position or radius"<<endl;
		exit(0);
	}
	cube *cubeNew;
	cubeNew = new cube;
	cubeNew->setLWH(l,h,w);
	cubeNew->setPosition(positionX, positionY, positionZ);
	cubeNew->init();
	m_drawManagers.push_back(cubeNew);
	m_animationManagers.push_back(cubeNew);
	m_timeManagers.push_back(cubeNew);
	m_clearManagers.push_back(cubeNew);
}

void ShZshapeManager::create_cylinder()
{
	cylinder *cylinderNew;
	cylinderNew = new cylinder;
	cylinderNew->init();
	m_drawManagers.push_back(cylinderNew);
	m_timeManagers.push_back(cylinderNew);
	m_animationManagers.push_back(cylinderNew);
	m_clearManagers.push_back(cylinderNew);
}

void ShZshapeManager::create_cylinder(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r, GLdouble h)
{
	if (positionX + r >= 1 || positionX - r <= -1 || positionZ + r >= 1 ||  positionZ - r <= -1 || positionY + h/2 >= 1 || positionY - h/2 <= -1)
	{
		cout<<"error position or radius"<<endl;
		exit(0);
	}
	cylinder *cylinderNew;
	cylinderNew = new cylinder;
	cylinderNew->setRH(r, h);
	cylinderNew->setPosition(positionX, positionY, positionZ);
	cylinderNew->init();
	m_drawManagers.push_back(cylinderNew);
	m_timeManagers.push_back(cylinderNew);
	m_animationManagers.push_back(cylinderNew);
	m_clearManagers.push_back(cylinderNew);
}

void ShZshapeManager::create_pipe()
{
	pipe *pipeNew;
	pipeNew = new pipe;
	pipeNew->init();
	m_drawManagers.push_back(pipeNew);
	m_timeManagers.push_back(pipeNew);
	m_animationManagers.push_back(pipeNew);
	m_clearManagers.push_back(pipeNew);
}

void ShZshapeManager::create_pipe(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble l_rin, GLdouble h_rout, GLdouble w_h)
{
	if (positionX + h_rout >= 1 || positionX - h_rout <= -1 || positionZ + h_rout >= 1 ||  positionZ - h_rout <= -1 || positionY + w_h/2 >= 1 || positionY - w_h/2 <= -1)
	{
		cout<<"error position or radius"<<endl;
		exit(0);
	}
	pipe *pipeNew;
	pipeNew = new pipe;
	pipeNew->setRH(l_rin, h_rout, w_h);
	pipeNew->setPosition(positionX, positionY, positionZ);
	pipeNew->init();
	m_drawManagers.push_back(pipeNew);
	m_timeManagers.push_back(pipeNew);
	m_animationManagers.push_back(pipeNew);
	m_clearManagers.push_back(pipeNew);
}

void ShZshapeManager::create_cone()
{
	cone *coneNew;
	coneNew = new cone;
	coneNew->init();
	m_drawManagers.push_back(coneNew);
	m_timeManagers.push_back(coneNew);
	m_animationManagers.push_back(coneNew);
	m_clearManagers.push_back(coneNew);
}

void ShZshapeManager::create_cone(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r, GLdouble h)
{
	if (positionX + r >= 1 || positionX - r <= -1 || positionZ + r >= 1 ||  positionZ - r <= -1 || positionY + h/2 >= 1 || positionY - h/2 <= -1)
	{
		cout<<"error position or radius"<<endl;
		exit(0);
	}
	cone *coneNew;
	coneNew = new cone;
	coneNew->setRH(r, h);
	coneNew->setPosition(positionX, positionY, positionZ);
	coneNew->init();
	m_drawManagers.push_back(coneNew);
	m_timeManagers.push_back(coneNew);
	m_animationManagers.push_back(coneNew);
	m_clearManagers.push_back(coneNew);
}

void ShZshapeManager::create_circle()
{
	circle *circleNew;
	circleNew = new circle;
	circleNew->init();
	m_drawManagers.push_back(circleNew);
	m_timeManagers.push_back(circleNew);
	m_animationManagers.push_back(circleNew);
	m_clearManagers.push_back(circleNew);
}

void ShZshapeManager::create_circle(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r)
{
	if (positionX + r >= 1 || positionX - r <= -1 || positionY + r >= 1 ||  positionY - r <= -1 || positionZ >= 1 || positionZ <= -1)
	{
		cout<<"error position or radius"<<endl;
		exit(0);
	}
	circle *circleNew;
	circleNew = new circle;
	circleNew->setR(r);
	circleNew->setPosition(positionX, positionY, positionZ);
	circleNew->init();
	m_drawManagers.push_back(circleNew);
	m_timeManagers.push_back(circleNew);
	m_animationManagers.push_back(circleNew);
	m_clearManagers.push_back(circleNew);
}

void ShZshapeManager::create_ring()
{
	ring *ringNew;
	ringNew = new ring;
	ringNew->init();
	m_drawManagers.push_back(ringNew);
	m_timeManagers.push_back(ringNew);
	m_animationManagers.push_back(ringNew);
	m_clearManagers.push_back(ringNew);
}

void ShZshapeManager::create_ring(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r)
{
	if (positionX + r >= 1 || positionX - r <= -1 || positionY + r >= 1 ||  positionY - r <= -1 || positionZ >= 1 || positionZ <= -1)
	{
		cout<<"error position or radius"<<endl;
		exit(0);
	}
	ring *ringNew;
	ringNew = new ring;
	ringNew->setR(r);
	ringNew->setPosition(positionX, positionY, positionZ);
	ringNew->init();
	m_drawManagers.push_back(ringNew);
	m_timeManagers.push_back(ringNew);
	m_animationManagers.push_back(ringNew);
	m_clearManagers.push_back(ringNew);
}

void ShZshapeManager::create_pyramid()
{
	pyramid *pyramidNew;
	pyramidNew = new pyramid;
	pyramidNew->init();
	m_drawManagers.push_back(pyramidNew);
	m_timeManagers.push_back(pyramidNew);
	m_animationManagers.push_back(pyramidNew);
	m_clearManagers.push_back(pyramidNew);
}

void ShZshapeManager::create_pyramid(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges_angles,  GLdouble r, GLdouble h)
{
	if (positionX + r >= 1 || positionX - r <= -1 || positionZ + r >= 1 ||  positionZ - r <= -1 || positionY + h/2 >= 1 || positionY - h/2 <= -1)
	{
		cout<<"error position or radius or height"<<endl;
		exit(0);
	}
	pyramid *pyramidNew;
	pyramidNew = new pyramid;
	pyramidNew->setPosition(positionX, positionY, positionZ);
	pyramidNew->setEdges(edges_angles);
	pyramidNew->setH(h);
	pyramidNew->setR(r);
	pyramidNew->init();
	m_drawManagers.push_back(pyramidNew);
	m_timeManagers.push_back(pyramidNew);
	m_animationManagers.push_back(pyramidNew);
	m_clearManagers.push_back(pyramidNew);
}

void ShZshapeManager::create_triangle()
{
	triangle *triangleNew;
	triangleNew = new triangle;
	triangleNew->init();
	m_drawManagers.push_back(triangleNew);
	m_timeManagers.push_back(triangleNew);
	m_animationManagers.push_back(triangleNew);
	m_clearManagers.push_back(triangleNew);
}

void ShZshapeManager::create_triangle(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r)
{
	if (positionX + r >= 1 || positionX - r <= -1 || positionY + r >= 1 ||  positionY - r <= -1 || positionZ >= 1 || positionZ <= -1)
	{
		cout<<"error position or radius or height"<<endl;
		exit(0);
	}
	triangle *triangleNew;
	triangleNew = new triangle;
	triangleNew->setPosition(positionX, positionY, positionZ);
	triangleNew->setR(r);
	triangleNew->init();
	m_drawManagers.push_back(triangleNew);
	m_timeManagers.push_back(triangleNew);
	m_animationManagers.push_back(triangleNew);
	m_clearManagers.push_back(triangleNew);
}

void ShZshapeManager::create_rectangle()
{
	rectangle *rectangleNew;
	rectangleNew = new rectangle;
	rectangleNew->init();
	m_drawManagers.push_back(rectangleNew);
	m_timeManagers.push_back(rectangleNew);
	m_animationManagers.push_back(rectangleNew);
	m_clearManagers.push_back(rectangleNew);
}

void ShZshapeManager::create_rectangle(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r)
{
	if (positionX + r >= 1 || positionX - r <= -1 || positionY + r >= 1 ||  positionY - r <= -1 || positionZ >= 1 || positionZ <= -1)
	{
		cout<<"error position or radius or height"<<endl;
		exit(0);
	}
	rectangle *rectangleNew;
	rectangleNew = new rectangle;
	rectangleNew->setPosition(positionX, positionY, positionZ);
	rectangleNew->setR(r);
	rectangleNew->init();
	m_drawManagers.push_back(rectangleNew);
	m_timeManagers.push_back(rectangleNew);
	m_animationManagers.push_back(rectangleNew);
	m_clearManagers.push_back(rectangleNew);
}

void ShZshapeManager::create_polygon()
{
	polygon *polygonNew;
	polygonNew = new polygon;
	polygonNew->init();
	m_drawManagers.push_back(polygonNew);
	m_timeManagers.push_back(polygonNew);
	m_animationManagers.push_back(polygonNew);
	m_clearManagers.push_back(polygonNew);
}

void ShZshapeManager::create_polygon(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges_angles,  GLdouble r)
{
	if (edges_angles < 5)
	{
		cout<<"warning:: polygon's edge must no less than 5"<<endl;
	}
	if (positionX + r >= 1 || positionX - r <= -1 || positionY + r >= 1 ||  positionY - r <= -1 || positionZ >= 1 || positionZ <= -1)
	{
		cout<<"error position or radius or height"<<endl;
		exit(0);
	}
	polygon *polygonNew;
	polygonNew = new polygon;
	polygonNew->setPosition(positionX, positionY, positionZ);
	polygonNew->setEdges(edges_angles);
	polygonNew->setR(r);
	polygonNew->init();
	m_drawManagers.push_back(polygonNew);
	m_timeManagers.push_back(polygonNew);
	m_animationManagers.push_back(polygonNew);
	m_clearManagers.push_back(polygonNew);
}

void ShZshapeManager::create_multigonalStar()
{
	multigonalStar *multigonalStarNew;
	multigonalStarNew = new multigonalStar;
	multigonalStarNew->init();
	m_drawManagers.push_back(multigonalStarNew);
	m_timeManagers.push_back(multigonalStarNew);
	m_animationManagers.push_back(multigonalStarNew);
	m_clearManagers.push_back(multigonalStarNew);
}

void ShZshapeManager::create_multigonalStar(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges_angles,  GLdouble r)
{
	if (edges_angles % 2 == 0 || edges_angles < 5)
	{
		cout<<"warning:: multigonalStar's angles must be no less than 5 and be odd number"<<endl;
		exit(0);
	}
	if (positionX + r >= 1 || positionX - r <= -1 || positionY + r >= 1 ||  positionY - r <= -1 || positionZ >= 1 || positionZ <= -1)
	{
		cout<<"error position or radius or height"<<endl;
		exit(0);
	}
	multigonalStar *multigonalStarNew;
	multigonalStarNew = new multigonalStar;
	multigonalStarNew->setPosition(positionX, positionY, positionZ);
	multigonalStarNew->setAngles(edges_angles);
	multigonalStarNew->setR(r);
	multigonalStarNew->init();
	m_drawManagers.push_back(multigonalStarNew);
	m_timeManagers.push_back(multigonalStarNew);
	m_animationManagers.push_back(multigonalStarNew);
	m_clearManagers.push_back(multigonalStarNew);
}

void ShZshapeManager::draw_cube()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "cube")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShader.vs", ".\\src\\resource\\fragmentShader.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}



void ShZshapeManager::draw_cylinder()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "cylinder")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShader.vs", ".\\src\\resource\\fragmentShader.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::draw_pipe()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "pipe")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShader.vs", ".\\src\\resource\\fragmentShader.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::draw_cone()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "cone")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShader.vs", ".\\src\\resource\\fragmentShader.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::draw_circle()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "circle")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShaderCommon.vs", ".\\src\\resource\\fragmentShaderCommon.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::draw_ring()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "ring")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShaderCommon.vs", ".\\src\\resource\\fragmentShaderCommon.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::draw_pyramid()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "pyramid")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShader.vs", ".\\src\\resource\\fragmentShader.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::draw_triangle()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "triangle")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShaderCommon.vs", ".\\src\\resource\\fragmentShaderCommon.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::draw_rectangle()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "rectangle")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShaderCommon.vs", ".\\src\\resource\\fragmentShaderCommon.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::draw_polygon()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "polygon")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShaderCommon.vs", ".\\src\\resource\\fragmentShaderCommon.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::draw_multigonalStar()
{
	int sizeOfDraw = m_drawManagers.size();
	ShZdrawManager* temp;
	string typeNm;
	for (int i=0; i<sizeOfDraw; i++)
	{
		m_drawManagers[i]->getTypeName(typeNm);
		if (typeNm == "multigonalStar")
		{
			temp = m_drawManagers[i];
			break;
		}
	}
	ShZshader *pShader;
	pShader = new ShZshader(".\\src\\resource\\vertexShaderCommon.vs", ".\\src\\resource\\fragmentShaderCommon.frag");
	temp->draw_shape(pShader);
	glDeleteProgram(pShader->programShader);
	delete pShader;
	pShader = nullptr;
}

void ShZshapeManager::unfold_cube()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "cube")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_cylinder()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "cylinder")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_pipe()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "pipe")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_cone()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "cone")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_circle()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "circle")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_ring()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "ring")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_pyramid()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "pyramid")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_triangle()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "triangle")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_rectangle()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "rectangle")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_polygon()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "polygon")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::unfold_multigonalStar()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "multigonalStar")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->unfold();
}

void ShZshapeManager::fold_cube()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "cube")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_cylinder()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "cylinder")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_pipe()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "pipe")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_cone()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "cone")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_circle()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "circle")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_ring()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "ring")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_pyramid()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "pyramid")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_triangle()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "triangle")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_rectangle()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "rectangle")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_polygon()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "polygon")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::fold_multigonalStar()
{
	int sizeOfAnimation;
	ShZanimationManager* temp;
	string typeNm;

	sizeOfAnimation = m_animationManagers.size();

	for (int i=0; i<sizeOfAnimation; i++)
	{
		m_animationManagers[i]->getTypeName(typeNm);
		if (typeNm == "multigonalStar")
		{
			temp = m_animationManagers[i];
			break;
		}
	}
	temp->fold();
}

void ShZshapeManager::begin_cube()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "cube")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_cylinder()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "cylinder")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_pipe()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "pipe")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_cone()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "cone")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_circle()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "circle")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_ring()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "ring")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_pyramid()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "pyramid")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_triangle()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "triangle")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_rectangle()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "rectangle")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_polygon()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "polygon")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::begin_multigonalStar()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "multigonalStar")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->begin();
}

void ShZshapeManager::end_cube()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "cube")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_cylinder()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "cylinder")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_pipe()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "pipe")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_cone()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "cone")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_circle()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "circle")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_ring()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "ring")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_pyramid()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "pyramid")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_triangle()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "triangle")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_rectangle()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "rectangle")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_polygon()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "polygon")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}

void ShZshapeManager::end_multigonalStar()
{
	int sizeOfTime;
	ShZtimeManager* temp;
	string typeNm;

	sizeOfTime = m_timeManagers.size();

	for (int i=0; i<sizeOfTime; i++)
	{
		m_timeManagers[i]->getTypeName(typeNm);
		if (typeNm == "multigonalStar")
		{
			temp = m_timeManagers[i];
			break;
		}
	}
	temp->end();
}
