#pragma once
#include"Shape.h"
class Oval:public shape
{
private:
	Point Center;
	int Horizonatl_diam;
	int Vertical_diam;
public:
	Oval(Point c, int h_d, int v_d, GfxInfo OvalInfo);
	~Oval();
	virtual void Draw(GUI* pUI) const;
	virtual string GetInfo() const;
	virtual Point GetCenter() const;
	virtual int GetHorDiam() const;
	virtual int GetVertDiam() const;
	void Resize(double factor) override;
	void Rotate()override;
	shape* Clone() const override;
	void Move(Point p);
	void Zoom(double factor, Point ref);
	virtual void Save(ofstream& OutFile);

};

