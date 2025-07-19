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
		int minx = min( P1.x, min(P2.x,P3.x) );
		int miny = min(P1.y, min(P2.y,P3.y));
		int Maxx = max(P1.x, max(P2.x,P3.x));
		int MaxY= max(P1.y, max(P2.y,P3.y));

		int paddingX = (Maxx - minx) * 0.15;
		int paddingY = (MaxY - miny) * 0.15;

		pUI->GetWindow()->DrawImage(img_path, minx+paddingX, miny+paddingY, (Maxx-minx)-2*paddingX, (MaxY-miny)-2*paddingY);
	}

}

string Tri::GetInfo() const
{
	return "Triangle with vertices at (" + to_string(P1.x) + ", " + to_string(P1.y) + "), " +
		"(" + to_string(P2.x) + ", " + to_string(P2.y) + "), " +
		"(" + to_string(P3.x) + ", " + to_string(P3.y) + ")";;
}

Point Tri::GetPoint1() const
{
	return P1;
}

Point Tri::GetPoint2() const
{
	return P2;
}

Point Tri::GetPoint3() const
{
	return P3;
}

double dist(const Point& p1,const Point& p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double anglebet2sides(double& l1, double& l2, double& l3) {
	double cosAngle = ((l2 * l2) + (l1 * l1) - (l3 * l3)) / (2 * l1 * l2);
	double angle = acos(cosAngle);
	return angle;
}

double areausingcoslaw(double& l1, double& l2, double& ang12) {
	double area = 0.5 * l1 * l2 * sin(ang12);
	return area;
}