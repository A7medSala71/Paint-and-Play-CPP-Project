#include "Rect.h"
#include"../GUI/GUI.h"
#include<iostream>
#include<fstream>
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

void Rect::Resize(double factor)
{
    Point center = { (Corner1.x + Corner2.x) / 2, (Corner1.y + Corner2.y) / 2 };
    Corner1.x = center.x + (Corner1.x - center.x) * factor;
    Corner1.y = center.y + (Corner1.y - center.y) * factor;
    Corner2.x = center.x + (Corner2.x - center.x) * factor;
    Corner2.y = center.y + (Corner2.y - center.y) * factor;
}

void Rect::Rotate()
{
    int cx = (Corner1.x + Corner2.x) / 2;
    int cy = (Corner1.y + Corner2.y) / 2;

    // Rotate corners
    int dx1 = Corner1.x - cx;
    int dy1 = Corner1.y - cy;
    int dx2 = Corner2.x - cx;
    int dy2 = Corner2.y - cy;

    Corner1.x = cx - dy1;
    Corner1.y = cy + dx1;

    Corner2.x = cx - dy2;
    Corner2.y = cy + dx2;
}

shape* Rect::Clone() const
{
    return new Rect(*this);
}

void Rect::Move(Point p)
{
    Point c;
    c.x = (Corner1.x + Corner2.x) / 2;
    c.y = (Corner1.y + Corner2.y) / 2;

    int dx = p.x - c.x;
    int dy = p.y - c.y;

    Corner1.x += dx; Corner1.y += dy;
    Corner2.x += dx; Corner2.y += dy;
}
void Rect::Zoom(double factor, Point ref)
{
    Corner1.x = ref.x + (int)((Corner1.x - ref.x) * factor);
    Corner1.y = ref.y + (int)((Corner1.y - ref.y) * factor);
    Corner2.x = ref.x + (int)((Corner2.x - ref.x) * factor);
    Corner2.y = ref.y + (int)((Corner2.y - ref.y) * factor);
}
void Rect::Save(ofstream& OutFile)
{
    OutFile << "RECT " << getID() << " "
        << Corner1.x << " " << Corner1.y << " "
        << Corner2.x << " " << Corner2.y << " "
        << (int)ShpGfxInfo.DrawClr.ucRed << " "
        << (int)ShpGfxInfo.DrawClr.ucGreen << " "
        << (int)ShpGfxInfo.DrawClr.ucBlue << " ";

    if (ShpGfxInfo.isFilled)
        OutFile << (int)ShpGfxInfo.FillClr.ucRed << " "
        << (int)ShpGfxInfo.FillClr.ucGreen << " "
        << (int)ShpGfxInfo.FillClr.ucBlue << " ";
    else
        OutFile << "NO_FILL ";

    OutFile << ShpGfxInfo.BorderWdth << "\n";
}
