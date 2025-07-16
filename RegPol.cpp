#include "Shapes/RegPol.h"
#define _USE_MATH_DEFINES 
#include <cmath>
#include<math.h>


RegPol::RegPol(Point center, Point radPT, int NOV, GfxInfo RegPolGfxInfo):shape(RegPolGfxInfo)
{
	numofvertices = NOV;
	array_x = new int[numofvertices];
	array_y = new int[numofvertices];

    double radius = sqrt(pow(radPT.x - center.x, 2) + pow(radPT.y - center.y, 2));
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


}
