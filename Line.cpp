#include "Shapes/Line.h"

Line::Line(Point p1, Point p2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{
	Corner1 = p1;
	Corner2 = p2;
}

Line::~Line()
{
}

void Line::Draw(GUI* pUI) const
{
	pUI->DrawLine(Corner1, Corner2, ShpGfxInfo);
}

string Line::GetInfo() const
{
	return "line from (" + to_string(Corner1.x) + ", " + to_string(Corner1.y) +
		") to (" + to_string(Corner2.x) + ", " + to_string(Corner2.y) + ")";
}

Point Line::GetStartPoint() const
{
	return Corner1;
}

Point Line::GetEndPoint() const
{
	return Corner2;
}
