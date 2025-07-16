#include"Shapes/pol.h"
pol::pol(int nov, int* arr_x, int*arr_y, GfxInfo RegPolGfxInfo):shape(RegPolGfxInfo)
{
	numofvertices = nov;
	array_x = new int[numofvertices];
	array_y = new int[numofvertices];

	for (int i = 0; i < numofvertices; ++i)
	{
		array_x[i] = arr_x[i];
		array_y[i] = arr_y[i];
	}
}

pol::~pol()
{
	delete[] array_x;
	delete[] array_y;
}

void pol::Draw(GUI* pUI) const
{
	pUI->DrawPol(numofvertices, array_x, array_y, ShpGfxInfo);
}
