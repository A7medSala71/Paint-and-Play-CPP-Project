#include"Shapes/Oval.h"
#include<iostream>
#include<fstream>
using namespace std;
Oval::Oval(Point c, int h_d, int v_d, GfxInfo OvalInfo):shape(OvalInfo)
{
	Center = c;
	Horizonatl_diam = h_d;
	Vertical_diam = v_d;
}

Oval::~Oval()
{
}

void Oval::Draw(GUI* pUI) const
{
	pUI->DrawOval(Center, Horizonatl_diam, Vertical_diam, ShpGfxInfo);


    if (!img_path.empty()) {
        float factor = 0.4f; // Adjust factor if needed
        int minx = Center.x - Horizonatl_diam / 2;
        int miny = Center.y - Vertical_diam / 2;
        int w = Horizonatl_diam;
        int h = Vertical_diam;
        int imgW = w * factor;
        int imgH = h * factor;
        int offsetX = minx + (w - imgW) / 2;
        int offsetY = miny + (h - imgH) / 2;

        pUI->GetWindow()->DrawImage(img_path, offsetX, offsetY, imgW, imgH);
    }

}

string Oval::GetInfo() const
{
	return "Oval centered at (" + to_string(Center.x) + ", " + to_string(Center.y) +
		"), width: " + to_string(Horizonatl_diam) + ", height: " + to_string(Vertical_diam);
}

Point Oval::GetCenter() const
{
	return Center;
}

int Oval::GetHorDiam() const
{
	return Horizonatl_diam;
}

int Oval::GetVertDiam() const
{
	return Vertical_diam;
}

void Oval::Resize(double factor)
{
    Horizonatl_diam = (int)(Horizonatl_diam * factor);
    Vertical_diam = (int)(Vertical_diam * factor);
}

void Oval::Rotate()
{
    swap(Horizonatl_diam, Vertical_diam);
}

shape* Oval::Clone() const
{
    return new Oval(*this);
}

void Oval::Move(Point p)
{
    Center = p;
}
void Oval::Zoom(double factor, Point ref)
{
    Center.x = ref.x + (int)((Center.x - ref.x) * factor);
    Center.y = ref.y + (int)((Center.y - ref.y) * factor);
    Horizonatl_diam = (int)(Horizonatl_diam * factor);
    Vertical_diam = (int)(Vertical_diam * factor);
}
void Oval::Save(ofstream& OutFile)
{
    OutFile << "OVAL " << getID() << " "
        << Center.x << " " << Center.y << " "
        << Horizonatl_diam << " " << Vertical_diam << " "
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
