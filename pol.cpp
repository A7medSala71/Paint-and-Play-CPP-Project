#include"Shapes/pol.h"
#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;
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
	if (!img_path.empty()) {
		float factor = 0.4f; // Adjust factor for better fit

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

string pol::GetInfo() const
{
	string info = "Polygon with " + to_string(numofvertices) + " vertices at: ";
	for (int i = 0; i < numofvertices; ++i) {
		info += "(" + to_string(array_x[i]) + ", " + to_string(array_y[i]) + ")";
		if (i < numofvertices - 1) info += ", ";
	}
	return info;
}

vector<Point> pol::GetVertices() const
{
	vector<Point> vertices;
	for (int i = 0; i < numofvertices; ++i) {
		vertices.push_back({ array_x[i], array_y[i] });
	}
	return vertices;
}

void pol::Resize(double factor)
{
	// Find centroid of polygon
	double sumX = 0, sumY = 0;
	for (int i = 0; i < numofvertices; ++i)
	{
		sumX += array_x[i];
		sumY += array_y[i];
	}
	double cx = sumX / numofvertices;
	double cy = sumY / numofvertices;

	// Scale vertices around centroid
	for (int i = 0; i < numofvertices; ++i)
	{
		array_x[i] = (int)(cx + (array_x[i] - cx) * factor);
		array_y[i] = (int)(cy + (array_y[i] - cy) * factor);
	}
}

void pol::Rotate()
{
}

shape* pol::Clone() const
{
	return new pol(numofvertices, array_x, array_y, ShpGfxInfo);
}

void pol::Move(Point p)
{
	// find centroid
	double sumx = 0, sumy = 0;
	for (int i = 0; i < numofvertices; i++) {
		sumx += array_x[i];
		sumy += array_y[i];
	}
	double cx = sumx / numofvertices;
	double cy = sumy / numofvertices;

	int dx = p.x - (int)cx;
	int dy = p.y - (int)cy;

	for (int i = 0; i < numofvertices; i++) {
		array_x[i] += dx;
		array_y[i] += dy;
	}
}

void pol::Zoom(double factor, Point ref)
{
	for (int i = 0; i < numofvertices; i++)
	{
		array_x[i] = ref.x + (int)((array_x[i] - ref.x) * factor);
		array_y[i] = ref.y + (int)((array_y[i] - ref.y) * factor);
	}
}

void pol::Save(ofstream& OutFile)
{
	OutFile << "POLY " << getID() << " " << numofvertices << " ";
	for (int i = 0; i < numofvertices; i++)
		OutFile << array_x[i] << " " << array_y[i] << " ";

	OutFile << (int)ShpGfxInfo.DrawClr.ucRed << " "
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



bool isPointInPolygon(const vector<Point>& poly, Point p) {
	int n = poly.size();
	int count = 0;
	for (int i = 0; i < n; ++i) {
		Point a = poly[i];
		Point b = poly[(i + 1) % n];

		if ((a.y > p.y) != (b.y > p.y)) {
			double xinters = (p.y - a.y) * (b.x - a.x) / double(b.y - a.y) + a.x;
			if (p.x < xinters)
				count++;
		}
	}
	return (count % 2) == 1;
}