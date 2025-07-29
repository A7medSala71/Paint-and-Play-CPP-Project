#pragma once
#include "Shape.h"
class Line: public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Line(Point p1, Point p2, GfxInfo shapeGfxInfo);
	virtual ~Line();
	virtual void Draw(GUI* pUI) const;
	virtual string GetInfo() const;
	virtual Point GetStartPoint() const;
	virtual Point GetEndPoint() const;
	void Resize(double factor) override;
	void Rotate()override;
	shape* Clone() const override;
	void Move(Point p);
	void Zoom(double factor, Point ref);
	virtual void Save(ofstream& OutFile);

};

