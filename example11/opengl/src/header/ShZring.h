#ifndef _SHZRING_H
#define _SHZRING_H

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

class ring :public ShZdrawManager, public ShZanimationManager, public ShZtimeManager, public ShZclearManager
{
public:
	ring();
	virtual ~ring();
	void init();
	void setTypeName(const char* p);
	void getTypeName(string &p);
	void setR(GLdouble r);
	void getR(GLdouble &r);
	void setTotalTime(double totalTime);
	virtual void draw_shape(ShZshader *pShader);
	virtual void unfold();
	virtual void fold();
	virtual void begin();
	virtual void end();
	virtual void clear();

protected:
private:
	void drawfaceL(ShZshader *pShader);
	void drawfaceR(ShZshader *pShader);
	void unfoldL();
	void unfoldR();
	void foldL();
	void foldR();
private:
	ShZMat4 m_projection,m_view;
	ShZMat4 m_model_l;
	ShZMat4 m_model_r;
	double m_totalTime;
	vector<double> m_angle_sl,m_angle_sr;
	clock_t m_start,m_current;
	GLuint m_vao, m_vbo;
	GLdouble m_R;                    
	int m_numberPoint;
	double offsetAngle;
	vector<int> m_index_l;
	vector<int> m_index_r;
	vector<VECTOR3D> m_vertices;
	vector<VECTOR3D> m_vertices_temp;
	string m_typeName;
};


#endif