#pragma once
#include"Shapes/Shape.h"
class Square:public shape
{
private:
	Point Center;
	int SideLength;
public:
	Square(Point p1, int length, GfxInfo shapeGfxInfo);
	virtual ~Square();
	virtual void Draw(GUI* pUI) const;
};

