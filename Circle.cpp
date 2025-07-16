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
