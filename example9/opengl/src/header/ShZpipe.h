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

class cylinder :public ShZdrawManager, public ShZanimationManager, public ShZtimeManager, public ShZclearManager
{
public:
	cylinder();
	virtual ~cylinder();
	void init();
	void setTypeName(const char* p);
	void getTypeName(string &p);
	void setRH(GLdouble r, GLdouble h);
	void getRH(GLdouble &r,GLdouble &h);
	void setTotalTime(double totalTime);
	virtual void draw_shape(ShZshader *pShader);
	virtual void unfold();
	virtual void fold();
	virtual void begin();
	virtual void end();
	virtual void clear();

protected:
private:
	void drawfacet(ShZshader *pShader);
	void drawfaceb(ShZshader *pShader);
	void drawfacesl(ShZshader *pShader);
	void drawfacesr(ShZshader *pShader);
	void drawRect(ShZshader *pShader);
	void unfoldt();
	void unfoldb();
	void unfoldsl();
	void unfoldsr();
	void foldt();
	void foldb();
	void foldsl();
	void foldsr();
private:
	ShZMat4 m_projection,m_view;
	ShZMat4 m_model_top;
	ShZMat4 m_model_bottom;
	ShZMat4 m_model_sidel;
	ShZMat4 m_model_sider;
	double m_totalTime;
	double m_angle_t,m_angle_b;
	vector<double> m_angle_sl,m_angle_sr;
	clock_t m_start,m_current;
	GLuint m_vao, m_vbo;
	//R: radius H: height
	GLdouble m_R, m_H;                    
	int m_numberPoint;
	double offsetAngle;
	vector<int> m_index_top;
	vector<int> m_index_bottom;
	vector<int> m_index_sidel;
	vector<int> m_index_sider;
	vector<VECTOR3D> m_vertices_s;
	vector<VECTOR3D> m_vertices_t;
	vector<VECTOR3D> m_vertices_b;
	vector<VECTOR3D> m_vertices_temp;
	string m_typeName;
};


#endif