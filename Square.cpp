#include "Square.h"

Square::Square( Point p1, int length, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Center = p1;
	SideLength = length;
}

Square::~Square()
{
}

void Square::Draw(GUI* pUI) const
{
	pUI->DrawSquare(Center,SideLength,ShpGfxInfo);
	if (!img_path.empty()) {
		int x = Center.x - SideLength / 2;
		int y = Center.y - SideLength / 2;

		pUI->GetWindow()->DrawImage(img_path, x, y, SideLength*0.90, SideLength*0.90);
	}
}

string Square::GetInfo() const
{
	return "Square centered at (" + to_string(Center.x) + ", " + to_string(Center.y) +
		") with side length " + to_string(SideLength);
}

Point Square::GetCenter() const
{
	return Center;
}

int Square::GetSlength() const
{
	return SideLength;
}

