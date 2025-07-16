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
		pUI->GetWindow()->DrawImage(img_path, x, y, SideLength, SideLength);
	}
}

