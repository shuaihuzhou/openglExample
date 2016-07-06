#ifndef _CUBE_H
#define _CUBE_H

#include "glew.h"
#include <stdlib.h>
#include "glut.h"
#include <iostream>
#include <time.h>

class cube
{
public:
	cube();
	~cube();
	void draw();
	void drawfacel();
	void drawfacer();
	void drawfacef();
	void drawfaceb();
	void drawfaceu();
	void drawfaced();
	void unfold();
	void unfoldl();
	void unfoldr();
	void unfoldb();
	void unfoldf();
	void unfoldu();
	void unfoldd();
	void fold();
	void foldl();
	void foldr();
	void foldb();
	void foldf();
	void foldu();
	void foldd();
	clock_t m_start,m_current;
	double m_totalTime;
	double m_anglel,m_angler,m_angleb,m_angleb2,m_anglef,m_angleu,m_angled;
	double f_x,f_y,f_z,f_x2,f_y2,f_z2;
protected:
private:
};

#endif // !_CUBE_H
