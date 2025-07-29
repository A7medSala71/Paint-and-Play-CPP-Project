#include"Shapes/Circle.h"
#include<fstream>
Circle::Circle(Point c, int r, GfxInfo circleInfo):shape(circleInfo)
{
	radius = r;
	center = c;
}

Circle::~Circle()
{
}

void Circle::Draw(GUI* pUI) const
{
	pUI->DrawCircle(center, radius, ShpGfxInfo);
    if (!img_path.empty()) {
        float factor = 0.5f; // smaller to fit inside circle
        int minx = center.x - radius;
        int miny = center.y - radius;
        int w = radius * 2;
        int h = radius * 2;
        int imgW = w * factor;
        int imgH = h * factor;
        int offsetX = minx + (w - imgW) / 2;
        int offsetY = miny + (h - imgH) / 2;

        pUI->GetWindow()->DrawImage(img_path, offsetX, offsetY, imgW, imgH);
    }
}

string Circle::GetInfo() const
{
	return "Circle centered at (" + to_string(center.x) + ", " + to_string(center.y) +
		") with radius " + to_string(radius);
}

Point Circle::getcenter() const
{
	return center;
}

int Circle::getrad() const
{
	return radius;
}

void Circle::Resize(double factor)
{
    radius = (int)(radius * factor);
}

void Circle::Rotate()
{
}

shape* Circle::Clone() const
{
    return new Circle(*this);
}

void Circle::Move(Point p)
{
    center = p;
}
void Circle::Zoom(double factor, Point ref)
{
    center.x = ref.x + (int)((center.x - ref.x) * factor);
    center.y = ref.y + (int)((center.y - ref.y) * factor);
    radius = (int)(radius * factor);
}

void Circle::Save(ofstream& OutFile)
{
    OutFile << "CIRCLE " << getID() << " "
        << center.x << " " << center.y << " "
        << radius << " "
        << (int)ShpGfxInfo.DrawClr.ucRed << " "
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


bool Circle::isinside(Point p)
{
    Point c = this->getcenter();
    int rad = this->getrad();
    int dx = p.x - c.x;
    int dy = p.y - c.y;
    if (dx * dx + dy * dy <= rad * rad)
        return true;
    else
        return false;
}
