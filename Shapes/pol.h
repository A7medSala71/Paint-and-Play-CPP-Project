#pragma once
#include"Shape.h"
#include<iostream>
#include<vector>
using namespace std;
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
	virtual string GetInfo() const;
	vector<Point> GetVertices() const;
	void Resize(double factor) override;
	void Rotate()override;
	shape* Clone() const override;
	void Move(Point p);
	void Zoom(double factor, Point ref);
	virtual void Save(ofstream& OutFile);

};

bool isPointInPolygon(const vector<Point>& poly, Point p);


