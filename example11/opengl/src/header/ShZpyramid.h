#ifndef _SHZPYRAMID_H
#define _SHZPYRAMID_H

#include <string>
#include "ShZDefine.h"
#include <time.h>
#include <vector>
#include "ShZMat4.h"
#include "ShZshader.h"
#include "ShZdrawManager.h"
#include "ShZanimationManager.h"
#include "ShZtimeManager.h"
#include "ShZclearManager.h"

class pyramid :public ShZdrawManager, public ShZanimationManager, public ShZtimeManager, public ShZclearManager
{
public:
	pyramid();
	~pyramid();
	void init(){}
private:

};



#endif