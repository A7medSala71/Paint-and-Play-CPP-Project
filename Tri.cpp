#include "Shapes/Tri.h"
#include"GUI/GUI.h"
#include<cmath>
#include<math.h>
#include<iostream>
#include<fstream>
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
		float factor = 0.4f;
		int minx = min( P1.x, min(P2.x,P3.x));
		int miny = min(P1.y, min(P2.y,P3.y));
		int Maxx = max(P1.x, max(P2.x,P3.x));
		int MaxY= max(P1.y, max(P2.y,P3.y));
		int w = (Maxx - minx);
		int h = (MaxY - miny);
		int imgW = w * factor;
		int imgH = h * factor;
		int offsetX = minx + (w - imgW) / 2;
		int offsetY = miny + (h - imgH) / 2;
		pUI->GetWindow()->DrawImage(img_path, offsetX, offsetY, imgW, imgH);
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

void Tri::Resize(double factor)
{
	// Calculate centroid
	double cx = (P1.x + P2.x + P3.x) / 3.0;
	double cy = (P1.y + P2.y + P3.y) / 3.0;

	// Scale points around centroid
	P1.x = (int)(cx + (P1.x - cx) * factor);
	P1.y = (int)(cy + (P1.y - cy) * factor);
	P2.x = (int)(cx + (P2.x - cx) * factor);
	P2.y = (int)(cy + (P2.y - cy) * factor);
	P3.x = (int)(cx + (P3.x - cx) * factor);
	P3.y = (int)(cy + (P3.y - cy) * factor);
}

void Tri::Rotate()
{
	// Compute centroid
	int cx = (P1.x + P2.x + P3.x) / 3;
	int cy = (P1.y + P2.y + P3.y) / 3;

	// Rotate each point
	auto rotate = [&](Point& p) {
		int dx = p.x - cx;
		int dy = p.y - cy;
		p.x = cx - dy;
		p.y = cy + dx;
		};

	rotate(P1);
	rotate(P2);
	rotate(P3);
}

shape* Tri::Clone() const
{
	return new Tri(*this);;
}

void Tri::Move(Point p)
{
	Point c;
	c.x = (P1.x + P2.x + P3.x) / 3;
	c.y = (P1.y + P2.y + P3.y) / 3;

	int dx = p.x - c.x;
	int dy = p.y - c.y;

	P1.x += dx; P1.y += dy;
	P2.x += dx; P2.y += dy;
	P3.x += dx; P3.y += dy;
}

void Tri::Zoom(double factor, Point ref)
{
	P1.x = ref.x + (int)((P1.x - ref.x) * factor);
	P1.y = ref.y + (int)((P1.y - ref.y) * factor);
	P2.x = ref.x + (int)((P2.x - ref.x) * factor);
	P2.y = ref.y + (int)((P2.y - ref.y) * factor);
	P3.x = ref.x + (int)((P3.x - ref.x) * factor);
	P3.y = ref.y + (int)((P3.y - ref.y) * factor);
}
void Tri::Save(ofstream& OutFile)
{
	OutFile << "TRIANGLE " << getID() << " "
		<< P1.x << " " << P1.y << " "
		<< P2.x << " " << P2.y << " "
		<< P3.x << " " << P3.y << " "
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