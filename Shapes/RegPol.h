#pragma once
#include"Shape.h"
class RegPol:public shape
{
private:
	int numofvertices;
	int* array_x;
	int* array_y;

public:
	RegPol(Point center, Point radPT, int NOV, GfxInfo RegPolGfxInfo);
	virtual ~RegPol();
	virtual void Draw(GUI* pUI) const;
};

