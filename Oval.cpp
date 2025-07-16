#include"Shapes/Oval.h"
Oval::Oval(Point c, int h_d, int v_d, GfxInfo OvalInfo):shape(OvalInfo)
{
	Center = c;
	Horizonatl_diam = h_d;
	Vertical_diam = v_d;
}

Oval::~Oval()
{
}

void Oval::Draw(GUI* pUI) const
{
	pUI->DrawOval(Center, Horizonatl_diam, Vertical_diam, ShpGfxInfo);
	if (!img_path.empty()) {
		int x = Center.x - Horizonatl_diam / 2;
		int y = Center.y - Horizonatl_diam / 2;
		pUI->GetWindow()->DrawImage(img_path, x, y, Horizonatl_diam, Vertical_diam);
	}

}
