#ifndef _SHZPIPE_H
#define _SHZPIPE_H

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

class pipe :public ShZdrawManager, public ShZanimationManager, public ShZtimeManager, public ShZclearManager
{
public:
	pipe();
	virtual ~pipe();
	void init();
	void setTypeName(const char* p);
	void getTypeName(string &p);
	void getRH(GLdouble &rinner, GLdouble &rout, GLdouble &h);
	void setRH(GLdouble rinner, GLdouble rout, GLdouble h);
	void setTotalTime(double totalTime);
	virtual void draw_shape(ShZshader *pShader);
	virtual void unfold();
	virtual void fold();
	virtual void begin();
	virtual void end();
	virtual void clear();

protected:
private:
	void drawfaceOutL(ShZshader *pShader);
	void drawfaceOutR(ShZshader *pShader);
	void drawfaceInnerL(ShZshader *pShader);
	void drawfaceInnerR(ShZshader *pShader);
	void unfoldOutL();
	void unfoldOutR();
	void unfoldInnerL();
	void unfoldInnerR();
	void foldOutL();
	void foldOutR();
	void foldInnerL();
	void foldInnerR();
private:
	ShZMat4 m_projection,m_view;
	ShZMat4 m_model_outL;
	ShZMat4 m_model_innerL;
	ShZMat4 m_model_outR;
	ShZMat4 m_model_innerR;
	double m_totalTime;
	vector<double> m_angle_innerL,m_angle_innerR;
	vector<double> m_angle_outL,m_angle_outR;
	clock_t m_start,m_current;
	GLuint m_vao, m_vbo;
	//R: radius H: height
	GLdouble m_R_inner, m_R_out, m_H;                    
	int m_numberPoint;
	double offsetAngle;
	vector<int> m_index_innerL;
	vector<int> m_index_innerR;
	vector<int> m_index_outL;
	vector<int> m_index_outR;
	vector<VECTOR3D> m_vertices_inner;
	vector<VECTOR3D> m_vertices_out;
	vector<VECTOR3D> m_vertices_tempInner;
	vector<VECTOR3D> m_vertices_tempOut;
	string m_typeName;
};


#endif