#include "Shapes/RegPol.h"
#define _USE_MATH_DEFINES 
#include <cmath>
#include<math.h>


RegPol::RegPol(Point center, Point radPT, int NOV, GfxInfo RegPolGfxInfo):shape(RegPolGfxInfo)
{
	numofvertices = NOV;
	array_x = new int[numofvertices];
	array_y = new int[numofvertices];
    Center = center;
    radius = sqrt(pow(radPT.x - center.x, 2) + pow(radPT.y - center.y, 2));
    double angleOffset = atan2(radPT.y - center.y, radPT.x - center.x);

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
    if (!img_path.empty())
    {
        int minX = *min_element(array_x, array_x + numofvertices);
        int maxX = *max_element(array_x, array_x + numofvertices);
        int minY = *min_element(array_y, array_y + numofvertices);
        int maxY = *max_element(array_y, array_y + numofvertices);

        int paddingX = (maxX - minX) * 0.15;
        int paddingY = (maxY - minY) * 0.15;

        pUI->GetWindow()->DrawImage(img_path, minX+ paddingX, minY+ paddingY, (maxX - minX)-(2*paddingX), (maxY - minY)-(2*paddingY));
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
