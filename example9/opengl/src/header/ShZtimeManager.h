/************************************************************************/
/* ShZtimamanager.h
/*Author: Shuaihu Zhou
/*Version: 1.0.1 
/* base class for controlling the time of animation
/************************************************************************/

#ifndef _SHZTIMEMANAGER_H
#define _SHZTIMEMANAGER_H

#include <string>

class ShZtimeManager
{
public:
	ShZtimeManager();
	virtual ~ShZtimeManager();
	virtual void getTypeName(std::string &p){}
	virtual void begin(){}
	virtual void end(){}

private:

};



#endif