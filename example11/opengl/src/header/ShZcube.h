#ifndef _SHZCUBE_H
#define _SHZCUBE_H

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

class cube :public ShZdrawManager, public ShZanimationManager, public ShZtimeManager, public ShZclearManager
{
public:
	cube();
	virtual ~cube(){}
	void init();
	void setTypeName(const char* p);
	virtual void getTypeName(string &p);
	void setLWH(GLdouble l, GLdouble h, GLdouble w);
	void getLWH(GLdouble &l,GLdouble &h, GLdouble &w);
	void setTotalTime(double totalTime);
	virtual void draw_shape(ShZshader *pShader);
	virtual void unfold();
	virtual void fold();
	virtual void begin();
	virtual void end();
	virtual void clear();

protected:
private:
	void drawfacel(ShZshader *pShader);
	void drawfacer(ShZshader *pShader);
	void drawfacef(ShZshader *pShader);
	void drawfaceb(ShZshader *pShader);
	void drawfaceu(ShZshader *pShader);
	void drawfaced(ShZshader *pShader);
	void unfoldl();
	void unfoldr();
	void unfoldb();
	void unfoldf();
	void unfoldu();
	void unfoldd();
	void foldl();
	void foldr();
	void foldb();
	void foldf();
	void foldu();
	void foldd();
private:
	ShZMat4 m_projection,m_view;
	ShZMat4 m_model_L;
	ShZMat4 m_model_R;
	ShZMat4 m_model_F;
	ShZMat4 m_model_B;
	ShZMat4 m_model_U;
	ShZMat4 m_model_D;
	double m_totalTime;
	double m_anglel,m_angler,m_angleb,m_angleb2,m_anglef,m_angleu,m_angled;
	clock_t m_start,m_current;
	GLuint m_vao,m_vbo;
	GLdouble m_L, m_H, m_W;
	vector<VECTOR3D> m_vertices;
	string m_typeName;
};

#endif // !_SHZCUBE_H
