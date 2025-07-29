#include "Shapes/RegPol.h"
#define _USE_MATH_DEFINES 
#include <cmath>
#include<math.h>
#include<fstream>


RegPol::RegPol(Point center, Point radPT, int NOV, GfxInfo RegPolGfxInfo):shape(RegPolGfxInfo)
{
	numofvertices = NOV;
	array_x = new int[numofvertices];
	array_y = new int[numofvertices];
    Center = center;
    radius = sqrt(pow(radPT.x - center.x, 2) + pow(radPT.y - center.y, 2));
    angleOffset = atan2(radPT.y - center.y, radPT.x - center.x);

    for (int i = 0; i < numofvertices; i++)
    {
        double angle = angleOffset + i * (2 * M_PI  / numofvertices);
        array_x[i] = static_cast<int>(center.x + radius * cos(angle));
        array_y[i] = static_cast<int>(center.y + radius * sin(angle));
    }
}

RegPol::~RegPol()
{
    delete[]array_x;
    delete[]array_y;
}

void RegPol::Draw(GUI* pUI) const
{
    pUI->DrawRegPol(numofvertices, array_x, array_y, ShpGfxInfo);
    if (!img_path.empty()) {
        float factor = 0.4f;

        int minx = array_x[0], maxx = array_x[0];
        int miny = array_y[0], maxy = array_y[0];

        for (int i = 1; i < numofvertices; i++) {
            minx = min(minx, array_x[i]);
            maxx = max(maxx, array_x[i]);
            miny = min(miny, array_y[i]);
            maxy = max(maxy, array_y[i]);
        }

        int w = maxx - minx;
        int h = maxy - miny;
        int imgW = w * factor;
        int imgH = h * factor;
        int offsetX = minx + (w - imgW) / 2;
        int offsetY = miny + (h - imgH) / 2;

        pUI->GetWindow()->DrawImage(img_path, offsetX, offsetY, imgW, imgH);
    }

}

string RegPol::GetInfo() const
{
    string info = "Polygon with " + to_string(numofvertices) + " vertices at: ";
    for (int i = 0; i < numofvertices; ++i) {
        info += "(" + to_string(array_x[i]) + ", " + to_string(array_y[i]) + ")";
        if (i < numofvertices - 1) info += ", ";
    }
    return info;
}

Point RegPol::Getcenter() const
{
    return Center;
}

double RegPol::GetRad() const
{
    return radius;
}

void RegPol::Resize(double factor)
{
    radius = (int)(radius * factor);
}

void RegPol::Rotate()
{
    // Add 90 degrees in radians
    angleOffset += M_PI / 2;
    if (angleOffset >= 2 * M_PI)
        angleOffset -= 2 * M_PI;

    // Recalculate vertex positions after rotation
    for (int i = 0; i < numofvertices; i++)
    {
        double angle = angleOffset + i * (2 * M_PI / numofvertices);
        array_x[i] = static_cast<int>(Center.x + radius * cos(angle));
        array_y[i] = static_cast<int>(Center.y + radius * sin(angle));
    }
}

shape* RegPol::Clone() const
{
    // Create a completely new RegPol with identical data
    RegPol* copy = new RegPol(*this);

    // Deep copy arrays (since default copy copied pointers only)
    copy->array_x = new int[numofvertices];
    copy->array_y = new int[numofvertices];
    for (int i = 0; i < numofvertices; ++i) {
        copy->array_x[i] = this->array_x[i];
        copy->array_y[i] = this->array_y[i];
    }

    return copy;
}

void RegPol::Move(Point p)
{
    int dx = p.x - Center.x;
    int dy = p.y - Center.y;

    Center.x = p.x;
    Center.y = p.y;

    for (int i = 0; i < numofvertices; i++) {
        array_x[i] += dx;
        array_y[i] += dy;
    }
}
void RegPol::Zoom(double factor, Point ref)
{
    Center.x = ref.x + (int)((Center.x - ref.x) * factor);
    Center.y = ref.y + (int)((Center.y - ref.y) * factor);
    radius *= factor;

    // Recompute vertices
    for (int i = 0; i < numofvertices; i++) {
        double angle = angleOffset + i * (2 * M_PI / numofvertices);
        array_x[i] = (int)(Center.x + radius * cos(angle));
        array_y[i] = (int)(Center.y + radius * sin(angle));
    }
}

void RegPol::Save(ofstream& OutFile)
{
    OutFile << "REGPOL " << getID() << " "
        << Center.x << " " << Center.y << " "
        << radius << " " << numofvertices << " "
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


