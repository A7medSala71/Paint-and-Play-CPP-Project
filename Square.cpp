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
    pUI->DrawSquare(Center, SideLength, ShpGfxInfo);
    if (!img_path.empty()) {
        float factor = 0.4f;
        int minx = Center.x - SideLength / 2;
        int miny = Center.y - SideLength / 2;
        int w = SideLength;
        int h = SideLength;
        int imgW = w * factor;
        int imgH = h * factor;
        int offsetX = minx + (w - imgW) / 2;
        int offsetY = miny + (h - imgH) / 2;

        pUI->GetWindow()->DrawImage(img_path, offsetX, offsetY, imgW, imgH);
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

