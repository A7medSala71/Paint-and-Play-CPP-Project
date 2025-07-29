#include "Shapes/Line.h"
#include<fstream>

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

void Line::Resize(double factor)
{
    Point center = { (Corner1.x + Corner2.x) / 2, (Corner1.y + Corner2.y) / 2 };

	Corner1.x = (int) (center.x + (Corner1.x - center.x) * factor);
	Corner1.y = (int)(center.y + (Corner1.y - center.y) * factor);

	Corner2.x = (int) (center.x + (Corner2.x - center.x) * factor);
	Corner2.y = (int) (center.y + (Corner2.y - center.y) * factor);
}

void Line::Rotate()
{
	int cx = (Corner1.x + Corner2.x) / 2;
	int cy = (Corner1.y + Corner2.y) / 2;

	int dx1 = Corner1.x - cx;
	int dy1 = Corner1.y - cy;
	int dx2 = Corner2.x - cx;
	int dy2 = Corner2.y - cy;

	Corner1.x = cx - dy1;
	Corner1.y = cy + dx1;

	Corner2.x = cx - dy2;
	Corner2.y = cy + dx2;
}

shape* Line::Clone() const
{
	return new Line(*this);
}

void Line::Move(Point p)
{
	Point mid;
	mid.x = (Corner1.x + Corner2.x) / 2;
	mid.y = (Corner1.y + Corner2.y) / 2;

	int dx = p.x - mid.x;
	int dy = p.y - mid.y;

	Corner1.x += dx; Corner1.y += dy;
	Corner2.x += dx; Corner2.y += dy;
}
void Line::Zoom(double factor, Point ref)
{
	Corner1.x = ref.x + (int)((Corner1.x - ref.x) * factor);
	Corner1.y = ref.y + (int)((Corner1.y - ref.y) * factor);
	Corner2.x = ref.x + (int)((Corner2.x - ref.x) * factor);
	Corner2.y = ref.y + (int)((Corner2.y - ref.y) * factor);
}
void Line::Save(ofstream& OutFile)
{
	OutFile << "LINE " << getID() << " "
		<< Corner1.x << " " << Corner1.y << " "
		<< Corner2.x << " " << Corner2.y << " "
		<< (int)ShpGfxInfo.DrawClr.ucRed << " "
		<< (int)ShpGfxInfo.DrawClr.ucGreen << " "
		<< (int)ShpGfxInfo.DrawClr.ucBlue << " "
		<< "NO_FILL "
		<< ShpGfxInfo.BorderWdth << "\n";
}
