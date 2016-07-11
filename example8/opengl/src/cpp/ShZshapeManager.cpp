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
}

void ShZshapeManager::clear()
{
	int sizeDrawManagers;
	int sizeAnimationManagers;
	int sizeTimeManagers;
	int sizeClearManagers;

	sizeDrawManagers = m_drawManagers.size();
	sizeAnimationManagers = m_animationManagers.size();
	sizeTimeManagers = m_timeManagers.size();
	sizeClearManagers = m_clearManagers.size();
	
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


