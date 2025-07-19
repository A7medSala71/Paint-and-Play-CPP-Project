#pragma once
#include"Shape.h"
class RegPol:public shape
{
private:
	int numofvertices;
	int* array_x;
	int* array_y;
	Point Center;
	double radius;

public:
	RegPol(Point center, Point radPT, int NOV, GfxInfo RegPolGfxInfo);
	virtual ~RegPol();
	virtual void Draw(GUI* pUI) const;
	virtual string GetInfo() const;
	virtual Point Getcenter() const;
	virtual double GetRad() const;


};

