#pragma once
#include"Shape.h"
class Tri:public shape
{
private:
	Point P1;
	Point P2;
	Point P3;
public:
	Tri(Point p1, Point p2, Point p3, GfxInfo shapeGfxInfo);
	virtual ~Tri();
	virtual void Draw(GUI* pUI) const;
	virtual string GetInfo() const;
	virtual Point GetPoint1() const;
	virtual Point GetPoint2() const;
	virtual Point GetPoint3() const;
	void Resize(double factor) override;
	void Rotate()override;
	shape* Clone() const override;
	void Move(Point p);
	void Zoom(double factor, Point ref);
	virtual void Save(ofstream& OutFile);
};

double dist(const Point& p1, const Point& p2);
double anglebet2sides(double& l1, double& l2, double& l3);
double areausingcoslaw(double& l1, double& l2, double& ang12);