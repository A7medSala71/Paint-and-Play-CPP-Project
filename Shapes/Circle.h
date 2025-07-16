#pragma once
#include"Shape.h"

class Circle:public shape
{
private:
	Point center;
	int radius;
public:
	Circle(Point c, int r, GfxInfo circleInfo);
	virtual ~Circle();
	virtual void Draw(GUI* pUI) const;
};

