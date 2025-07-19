#include"Shapes/Circle.h"
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
		int left = center.x - radius;
		int top = center.y - radius;
		pUI->GetWindow()->DrawImage(img_path, left, top, 2 * radius, 2 * radius);
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
