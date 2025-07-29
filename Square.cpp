#include "Square.h"
#include<fstream>

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

void Square::Resize(double factor)
{
    SideLength = (int)(SideLength * factor);
}

void Square::Rotate()
{
}

shape* Square::Clone() const
{
    return new Square(*this);
}

void Square::Move(Point p)
{
    Center = p;
}
void Square::Zoom(double factor, Point ref)
{
    Center.x = ref.x + (int)((Center.x - ref.x) * factor);
    Center.y = ref.y + (int)((Center.y - ref.y) * factor);
    SideLength = (int)(SideLength * factor);
}
void Square::Save(ofstream& OutFile)
{
    OutFile << "SQUARE " << getID() << " "
        << Center.x << " " << Center.y << " "
        << SideLength << " "
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
