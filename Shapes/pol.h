#pragma once
#include"Shape.h"
class pol:public shape
{
private:
	int numofvertices;
	int* array_x;
	int* array_y;

public:
	pol(int nov, int* arr_x, int*arr_y, GfxInfo RegPolGfxInfo);
	virtual ~pol();
	virtual void Draw(GUI* pUI) const;
};

