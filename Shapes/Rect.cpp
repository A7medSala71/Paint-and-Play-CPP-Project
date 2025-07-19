#include "Rect.h"
#include"../GUI/GUI.h"

Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}

Rect::~Rect()
{}

void Rect::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
    if (!img_path.empty()) {
        int x1 = min(Corner1.x, Corner2.x);
        int y1 = min(Corner1.y, Corner2.y);
        int x2 = max(Corner1.x, Corner2.x);
        int y2 = max(Corner1.y, Corner2.y);
        int width = x2 - x1;
        int height = y2 - y1;

        pUI->GetWindow()->DrawImage(img_path, x1, y1, width, height);
    }
}

string Rect::GetInfo() const
{
    return "Rectangle from (" + to_string(Corner1.x) + ", " + to_string(Corner1.y) +
        ") to (" + to_string(Corner2.x) + ", " + to_string(Corner2.y) + ")";
}

Point Rect::getCorner1() const
{
    return Corner1;
}

Point Rect::getCorner2() const
{
    return Corner2;
}
