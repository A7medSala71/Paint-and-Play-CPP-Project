#pragma once

#include "shape.h"

class Rect : public shape
{
private:
	Point Corner1;	
	Point Corner2;
public:
	Rect(Point , Point, GfxInfo shapeGfxInfo );
	virtual ~Rect();
	virtual void Draw(GUI* pUI) const;
	virtual string GetInfo() const;
	Point getCorner1() const;
	Point getCorner2() const;
	void Resize(double factor) override;
	void Rotate()override;
	shape* Clone() const override;
	void Move(Point p);
	void Zoom(double factor, Point ref);
	virtual void Save(ofstream& OutFile);
};

