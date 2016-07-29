#ifndef _SHZCONE_H
#define _SHZCONE_H

#include <string>
#include "ShZDefine.h"
#include <time.h>
#include <cmath>
#include <vector>
#include "ShZMat4.h"
#include "ShZshader.h"
#include "ShZdrawManager.h"
#include "ShZanimationManager.h"
#include "ShZtimeManager.h"
#include "ShZclearManager.h"

class cone :public ShZdrawManager, public ShZanimationManager, public ShZtimeManager, public ShZclearManager
{
public:
	cone();
	virtual ~cone();
	void init();
	void setTypeName(const char* p);
	void getTypeName(string &p);
	void getPosition(GLdouble &positionX, GLdouble &positionY, GLdouble &positionZ);
	void setPosition(GLdouble positionX, GLdouble positionY, GLdouble positionZ);
	void getRH(GLdouble &r, GLdouble &h);
	void setRH(GLdouble r, GLdouble h);
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
	void drawfaceSl(ShZshader *pShader);
	void drawfaceSr(ShZshader *pShader);
	void drawfaceCompensatin(ShZshader *pShader);
	void unfoldSl();
	void unfoldSr();
	void foldSl();
	void foldSr();
private:
	ShZMat4 m_projection,m_view;
	ShZMat4 m_model_sl;
	ShZMat4 m_model_sr;
	ShZMat4 m_model_compensation;
	double m_totalTime;
	vector<double> m_angle_sL_step1,m_angle_sL_step2,m_angle_sR_step1,m_angle_sR_step2;
	clock_t m_start,m_current;
	GLuint m_vao, m_vbo, m_nbo;
	//R: radius H: height
	GLdouble m_R, m_H, m_generatrix;
	GLdouble m_unfoldedAngle;
	GLdouble m_positionX, m_positionY, m_positionZ;
	int m_numberPoint;
	double offsetAngle;
	double offsetNewAngle;
	vector<int> m_index_sL;
	vector<int> m_index_sR;
	vector<int> m_index_compensation;
	vector<VECTOR3D> m_vertices;
	vector<VECTOR3D> m_vertices_temp;
	vector<VECTOR3D> m_normals;
	VECTOR3D m_viewPosition,m_lightPosition,m_lightColor,m_objectColor;
	string m_typeName;
	animationState state;
};


#endif