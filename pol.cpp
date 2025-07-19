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
	if (!img_path.empty())
	{
		int minX = *min_element(array_x, array_x + numofvertices);
		int maxX = *max_element(array_x, array_x + numofvertices);
		int minY = *min_element(array_y, array_y + numofvertices);
		int maxY = *max_element(array_y, array_y + numofvertices);

		int paddingX = (maxX - minX) * 0.15;
		int paddingY = (maxY - minY) * 0.15;
		pUI->GetWindow()->DrawImage(img_path, minX + paddingX, minY + paddingY, (maxX - minX) - (2 * paddingX), (maxY - minY)-(2*paddingY));
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
