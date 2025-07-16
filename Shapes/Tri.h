#pragma once
#include"Shape.h"
class Tri:public shape
{
private:
	Point P1;
	Point P2;
	Point P3;
public:
	Tri(Point p1, Point p2, Point p3, GfxInfo shapeGfxInfo);
	virtual ~Tri();
	virtual void Draw(GUI* pUI) const;
};

