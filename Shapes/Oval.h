#pragma once
#include"Shape.h"
class Oval:public shape
{
private:
	Point Center;
	int Horizonatl_diam;
	int Vertical_diam;
public:
	Oval(Point c, int h_d, int v_d, GfxInfo OvalInfo);
	~Oval();
	virtual void Draw(GUI* pUI) const;

};

