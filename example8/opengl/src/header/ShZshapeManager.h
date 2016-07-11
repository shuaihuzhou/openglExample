/************************************************************************/
/* ShZshapeManager.h
/*Author: Shuaihu Zhou
/*Version: 1.0.0 header is ShZshape.h
/*Version: 1.0.1
/*Specification: thiis is the main interface class of the desired library.
/************************************************************************/


#ifndef _SHZSHAPE_H
#define _SHZSHAPE_H
#include <vector>
#include "ShZdrawManager.h"
#include "ShZanimationManager.h"
#include "ShZtimeManager.h"
#include "ShZcube.h"
#include "ShZshader.h"
#include "ShZcylinder.h"
#include "ShZclearManager.h"

class ShZshapeManager
{
public:
	ShZshapeManager();
	~ShZshapeManager();

	void create_shape(const char* content);
	void draw_shape(const char* content);
	void unfold_shape(const char* content);
	void fold_shape(const char* content);
	void begin(const char* content);
	void end(const char* content);
	void clear();
	vector<ShZdrawManager*> getDrawManager();
	vector<ShZanimationManager*> getAnimationManager();
	vector<ShZtimeManager*> getTimeManager();
protected:
	void create_cube();
	void create_cylinder();
	void draw_cube();
	void draw_cylinder();
	void unfold_cube();
	void unfold_cylinder();
	void fold_cube();
	void fold_cylinder();
	void begin_cube();
	void end_cube();
	void begin_cylinder();
	void end_cylinder();
	vector<ShZdrawManager*> m_drawManagers;
	vector<ShZanimationManager*> m_animationManagers;
	vector<ShZtimeManager*> m_timeManagers;
	vector<ShZclearManager*> m_clearManagers;
};



#endif