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
#include "ShZtriangle.h"
#include "ShZrectangle.h"
#include "ShZpolygon.h"
#include "ShZmultigonalStar.h"


class ShZshapeManager
{
public:
	ShZshapeManager();
	~ShZshapeManager();

	void create_shape(const char* content);

	/************************************************************************/
	/* this interface can create shapes: circle, ring, cube, cylinder, cone,
	/* multigonalStar, pipe, polygon, pyramid, rectangle, triangle with default
	/* parameter.
	/************************************************************************/

	void create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r);

	/************************************************************************/
	/* this interface is an overload interface
	/* it can be used to assign the position
	/* it can be used to assign the radius of circle or ring.
	/* it can be also used to assign the circumcircle radius of the rectangle, triangle 
	/************************************************************************/

	void create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r, GLdouble h);

	/************************************************************************/
	/* this interface is an overload interface
	/* it can be used to assign the position
	/* it can be used to assign the radius and height of cylinder, cone
	/************************************************************************/

	void create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges_angles, GLdouble r);

	/************************************************************************/
	/* this interface is an overload interface
	/* it can be used to assign the position
	/* it can be used to assign the radius and edges of polygon and multigonalStar
	/************************************************************************/

	void create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges, GLdouble h, GLdouble r);

	/************************************************************************/
	/* this interface is an overload interface
	/* it can be used to assign the position
	/* it can be used to assign the edges, height and circumcicle radius of pyramid. 
	/************************************************************************/

	void create_shape(const char* content, GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble l_rin, GLdouble h_rout, GLdouble w_h);

	/************************************************************************/
	/* this interface is an overload interface
	/* it can be used to assign the position
	/* it can be used to assign the length, height, width of cube/cuboid.
	/* it can be used to assign the rInner, rOut, height of pipe.
	/************************************************************************/

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
	void create_cube(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble l, GLdouble h, GLdouble w);
	void create_cylinder();
	void create_cylinder(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r, GLdouble h);
	void create_pipe();
	void create_pipe(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble l_rin, GLdouble h_rout, GLdouble w_h);
	void create_cone();
	void create_cone(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r, GLdouble h);
	void create_circle();
	void create_circle(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r);
	void create_ring();
	void create_ring(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r);
	void create_pyramid();
	void create_pyramid(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges_angles, GLdouble r, GLdouble h);
	void create_triangle();
	void create_triangle(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r);
	void create_rectangle();
	void create_rectangle(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLdouble r);
	void create_polygon();
	void create_polygon(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges,  GLdouble r);
	void create_multigonalStar();
	void create_multigonalStar(GLdouble positionX, GLdouble positionY, GLdouble positionZ, GLint edges_angles,  GLdouble r);

	void draw_cube();
	void draw_cylinder();
	void draw_pipe();
	void draw_cone();
	void draw_circle();
	void draw_ring();
	void draw_pyramid();
	void draw_triangle();
	void draw_rectangle();
	void draw_polygon();
	void draw_multigonalStar();

	void unfold_cube();
	void unfold_cylinder();
	void unfold_pipe();
	void unfold_cone();
	void unfold_circle();
	void unfold_ring();
	void unfold_pyramid();
	void unfold_triangle();
	void unfold_rectangle();
	void unfold_polygon();
	void unfold_multigonalStar();

	void fold_cube();
	void fold_cylinder();
	void fold_pipe();
	void fold_cone();
	void fold_circle();
	void fold_ring();
	void fold_pyramid();
	void fold_triangle();
	void fold_rectangle();
	void fold_polygon();
	void fold_multigonalStar();

	void begin_cube();
	void begin_cylinder();
	void begin_pipe();
	void begin_cone();
	void begin_circle();
	void begin_ring();
	void begin_pyramid();
	void begin_triangle();
	void begin_rectangle();
	void begin_polygon();
	void begin_multigonalStar();

	void end_cube();
	void end_cylinder();
	void end_pipe();
	void end_cone();
	void end_circle();
	void end_ring();
	void end_pyramid();
	void end_triangle();
	void end_rectangle();
	void end_polygon();
	void end_multigonalStar();

	vector<ShZdrawManager*> m_drawManagers;
	vector<ShZanimationManager*> m_animationManagers;
	vector<ShZtimeManager*> m_timeManagers;
	vector<ShZclearManager*> m_clearManagers;
};



#endif