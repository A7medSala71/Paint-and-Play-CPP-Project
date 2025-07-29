#pragma once
#include"Shapes/Shape.h"
class Square:public shape
{
private:
	Point Center;
	int SideLength;
public:
	Square(Point p1, int length, GfxInfo shapeGfxInfo);
	virtual ~Square();
	virtual void Draw(GUI* pUI) const;
	virtual string GetInfo() const;
	virtual Point GetCenter() const;
	virtual int GetSlength() const;
	void Resize(double factor) override;
	void Rotate()override;
	shape* Clone() const override;
	void Move(Point p);
	void Zoom(double factor, Point ref);
	virtual void Save(ofstream& OutFile);

};

