/************************************************************************/
/* ShZanimationManager.h
/*Author: Shuaihu Zhou
/*Version: 1.0 animation.h
/*Version: 1.0.1 
/* base class for controlling the motion of animation
/************************************************************************/
#ifndef _SHZANIMATION_H
#define _SHZANIMATION_H

#include <string>

class ShZanimationManager
{
public:
	ShZanimationManager();
	virtual ~ShZanimationManager();
	virtual void unfold(){}	
	virtual void fold(){}
	virtual void getTypeName(std::string &p){}

};

#endif