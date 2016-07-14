/************************************************************************/
/* ShZdrawManager.h
/*Author: Shuaihu Zhou
/*Version: 1.0 node.h
/*Version: 1.0.1 
/* base class for controlling the drawing
/************************************************************************/

#ifndef _SHZDRAWMANAGER_H
#define _SHZDRAWMANAGER_H

#include <string>
#include "ShZshader.h"

class ShZdrawManager
{
public:
	ShZdrawManager();
	virtual ~ShZdrawManager();
	virtual void getTypeName(std::string &p){}
	virtual void draw_shape(ShZshader *pShader){}
private:

};

#endif





