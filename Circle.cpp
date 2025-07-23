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
