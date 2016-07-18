/************************************************************************/
/* ShZshapeManager.h
/*Author: Shuaihu Zhou
/*Version: 1.0.0 header is ShZshape.h
/*Version: 1.0.1
/*Specification: this is the main interface class of the desired library.
/************************************************************************/


#ifndef _SHZSHAPE_H
#define _SHZSHAPE_H
#include <vector>
#include "ShZdrawManager.h"
#include "ShZanimationManager.h"
#include "ShZtimeManager.h"
#include "ShZclearManager.h"
#include "ShZshader.h"
#include "ShZcube.h"
#include "ShZcylinder.h"
#include "ShZpipe.h"
#include "ShZcone.h"
#include "ShZcircle.h"
#include "ShZring.h"
#include "ShZpyramid.h"


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
private:
	void create_cube();
	void create_cylinder();
	void create_pipe();
	void create_cone();
	void create_circle();
	void create_ring();
	void create_pyramid();
	void draw_cube();
	void draw_cylinder();
	void draw_pipe();
	void draw_cone();
	void draw_circle();
	void draw_ring();
	void draw_pyramid();
	void unfold_cube();
	void unfold_cylinder();
	void unfold_pipe();
	void unfold_cone();
	void unfold_circle();
	void unfold_ring();
	void unfold_pyramid();
	void fold_cube();
	void fold_cylinder();
	void fold_pipe();
	void fold_cone();
	void fold_circle();
	void fold_ring();
	void fold_pyramid();
	void begin_cube();
	void begin_cylinder();
	void begin_pipe();
	void begin_cone();
	void begin_circle();
	void begin_ring();
	void begin_pyramid();
	void end_cube();
	void end_cylinder();
	void end_pipe();
	void end_cone();
	void end_circle();
	void end_ring();
	void end_pyramid();
	vector<ShZdrawManager*> m_drawManagers;
	vector<ShZanimationManager*> m_animationManagers;
	vector<ShZtimeManager*> m_timeManagers;
	vector<ShZclearManager*> m_clearManagers;
};



#endif