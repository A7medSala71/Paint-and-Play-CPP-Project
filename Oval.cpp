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

		pUI->GetWindow()->DrawImage(img_path, x, y, Horizonatl_diam*0.8, Vertical_diam*0.8);
	}

}

string Oval::GetInfo() const
{
	return "Oval centered at (" + to_string(Center.x) + ", " + to_string(Center.y) +
		"), width: " + to_string(Horizonatl_diam) + ", height: " + to_string(Vertical_diam);
}

Point Oval::GetCenter() const
{
	return Center;
}

int Oval::GetHorDiam() const
{
	return Horizonatl_diam;
}

int Oval::GetVertDiam() const
{
	return Vertical_diam;
}
