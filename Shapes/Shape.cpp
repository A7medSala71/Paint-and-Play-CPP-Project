#include "shape.h"

shape::shape(GfxInfo shapeGfxInfo):ID(-1)
{ 
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
}
 
void shape::SetSelected(bool s)
{	ShpGfxInfo.isSelected = s; }

bool shape::IsSelected() const
{	return ShpGfxInfo.isSelected; }

void shape::ChngDrawClr(color Dclr)
{	ShpGfxInfo.DrawClr = Dclr; }

void shape::ChngFillClr(color Fclr)
{	
	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr; 
}

void shape::setBorderColor(const color& newColor)
{
	ShpGfxInfo.DrawClr = newColor;  // assuming ShpGfxInfo contains the border color

}

color shape::getBorderColor() const
{
	return ShpGfxInfo.DrawClr;
}

color shape::getFillColor() const
{
	return ShpGfxInfo.FillClr;
}

void shape::setFillColor(const color& newColor)
{
	ShpGfxInfo.FillClr = newColor;
}

bool shape::Isfilled() const
{
	return ShpGfxInfo.isFilled;
}

void shape::setIsFilled(bool Fillstate)
{
	ShpGfxInfo.isFilled = Fillstate;
}

void shape::setImagePath(const string& path)
{
	img_path = path;
}

string shape::getImagePath() const
{
	return img_path;
}

int shape::getID() const
{
	return ID;
}

void shape::setID(int newID)
{
	ID = newID;
}
