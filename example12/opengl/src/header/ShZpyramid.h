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
	void init();
	void setTypeName(const char* p);
	void getTypeName(string &p);
	void getPosition(GLdouble &positionX, GLdouble &positionY, GLdouble &positionZ);
	void setPosition(GLdouble positionX, GLdouble positionY, GLdouble positionZ);
	void getR(GLdouble &r);
	void setR(GLdouble r);
	void getH(GLdouble &h);
	void setH(GLdouble h);
	void getEdges(GLdouble &edges);
	void setEdges(GLdouble edges);
	void setTotalTime(double totalTime);
	virtual void draw_shape(ShZshader *pShader);
	virtual void unfold();
	virtual void fold();
	virtual void begin();
	virtual void end();
	virtual void clear();

protected:
private:
	void drawface(ShZshader *pShader);
	void unfoldface();
	void foldface();
private:
	ShZMat4 m_projection,m_view;
	ShZMat4 m_model;
	double m_totalTime;
	clock_t m_start,m_current;
	GLuint m_vao, m_vbo, m_nbo;
	//R: radius
	GLdouble m_H;
	GLdouble m_R;
	GLdouble m_positionX, m_positionY, m_positionZ;
	int m_numberPoint;
	double offsetAngle;
	vector<int> m_index;
	vector<VECTOR3D> m_vertices;
	vector<VECTOR3D> m_normals;
	VECTOR3D m_viewPosition,m_lightPosition,m_lightColor,m_objectColor;
	string m_typeName;
};



#endif