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
	pShader = new ShZshader("./src/resource/vertexShader.vs", "./src/resource/fragmentShader.frag");
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
	pShader = new ShZshader("./src/resource/vertexShader.vs", "./src/resource/fragmentShader.frag");
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
	pShader = new ShZshader("./src/resource/vertexShader.vs", "./src/resource/fragmentShader.frag");
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
	pShader = new ShZshader("./src/resource/vertexShader.vs", "./src/resource/fragmentShader.frag");
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
	pShader = new ShZshader("./src/resource/vertexShader.vs", "./src/resource/fragmentShader.frag");
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
	pShader = new ShZshader("./src/resource/vertexShader.vs", "./src/resource/fragmentShader.frag");
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
	pShader = new ShZshader("./src/resource/vertexShader.vs", "./src/resource/fragmentShader.frag");
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
