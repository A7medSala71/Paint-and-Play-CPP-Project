#include "Rect.h"
#include"../GUI/GUI.h"
#include<iostream>
using namespace std;
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
        float factor = 0.4f;
        int minx = min(Corner1.x, Corner2.x);
        int miny = min(Corner1.y, Corner2.y);
        int maxx = max(Corner1.x, Corner2.x);
        int maxy = max(Corner1.y, Corner2.y);

        int w = maxx - minx;
        int h = maxy - miny;
        int imgW = w * factor;
        int imgH = h * factor;
        int offsetX = minx + (w - imgW) / 2;
        int offsetY = miny + (h - imgH) / 2;

        pUI->GetWindow()->DrawImage(img_path, offsetX, offsetY, imgW, imgH);
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
