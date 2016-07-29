#ifndef _SHZCYLINDER_H
#define _SHZCYLINDER_H

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
	void setPosition(GLdouble positionX, GLdouble positionY, GLdouble positionZ);
	void getPosition(GLdouble &positionX, GLdouble &positionY, GLdouble &positionZ);
	void setRH(GLdouble r, GLdouble h);
	void getRH(GLdouble &r,GLdouble &h);
	void setTotalTime(double totalTime);
	virtual void draw_shape(ShZshader *pShader);
	virtual void unfold();
	virtual void fold();
	virtual void begin();
	virtual void end();
	virtual void clear();

	enum animationState{OPENING, OPENED, CLOSING,CLOSED};

protected:
private:
	void drawfacet(ShZshader *pShader);
	void drawfaceb(ShZshader *pShader);
	void drawfacesl(ShZshader *pShader);
	void drawfacesr(ShZshader *pShader);
	void drawfaceCompensation(ShZshader *pShader);
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
	GLuint m_vao, m_vbo, m_nbo;
	//R: radius H: height
	GLdouble m_positionX, m_positionY, m_positionZ;
	GLdouble m_R, m_H;                    
	int m_numberPoint;
	double offsetAngle;
	vector<int> m_index_top;
	vector<int> m_index_bottom;
	vector<int> m_index_sidel;
	vector<int> m_index_sider;
	vector<int> m_index_compensation;
	vector<VECTOR3D> m_vertices_s;
	vector<VECTOR3D> m_vertices_t;
	vector<VECTOR3D> m_vertices_b;
	vector<VECTOR3D> m_vertices_temp;
	vector<VECTOR3D> m_normals_s,m_normals_t,m_normals_b;
	VECTOR3D m_viewPosition,m_lightPosition,m_lightColor,m_objectColor;
	string m_typeName;
	animationState state;
};


#endif