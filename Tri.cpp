#include "Shapes/Tri.h"
#include"GUI/GUI.h"
#include<cmath>
#include<math.h>
#include<iostream>
using namespace std;

Tri::Tri(Point p1, Point p2, Point p3, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{
	P1 = p1;
	P2 = p2;
	P3 = p3;
}

Tri::~Tri()
{
}

void Tri::Draw(GUI* pUI) const
{
	pUI->DrawTri(P1, P2,  P3, ShpGfxInfo);

	if (!img_path.empty()) {
		int minx = min(P1.x, P2.x,P3.x);
		int miny = min(P1.y, P2.y,P3.y);
		int Maxx = max(P1.x, P2.x,P3.x);
		int MaxY= max(P1.y, P2.y,P3.y);
		pUI->GetWindow()->DrawImage(img_path, minx, miny, Maxx-minx, MaxY-miny);
	}
}
