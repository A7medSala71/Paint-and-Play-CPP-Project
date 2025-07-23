#include"Shapes/pol.h"
#include<iostream>
#include<algorithm>
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
