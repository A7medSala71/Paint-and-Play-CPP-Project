#include"operations/opAddOval.h"
#include"Shapes/Oval.h"
#include"GUI/GUI.h"
#include"controller.h"

opAddOval::opAddOval(controller* pCont):operation(pCont)
{
}

opAddOval::~opAddOval()
{
}

void opAddOval::Execute()
{
	Point Center;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Oval: Click at Center");
	pUI->GetPointClicked(Center.x, Center.y);

	string msg = "center is at (" + to_string(Center.x) + ", " + to_string(Center.y) + " )";
	pUI->PrintMessage(msg);

	pUI->PrintMessage("Enter Horizontal Diameter: ");
	string hd = pUI->GetSrting();
	int Hor_Dia = stoi(hd);

	pUI->PrintMessage("Enter Vertical Diameter: ");
	string vd = pUI->GetSrting();
	int Ver_Dia = stoi(vd);

	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo OvalGfxInfo;

	//get drawing, filling colors and pen width from the interface
	OvalGfxInfo.DrawClr = pUI->getCrntDrawColor();
	OvalGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	OvalGfxInfo.isSelected = false;	//defualt is not selected

	OvalGfxInfo.isFilled = pUI->getIsFilled();
	if (OvalGfxInfo.isFilled)
		OvalGfxInfo.FillClr = pUI->getCrntFillColor();

	pOVAL = new Oval(Center, Hor_Dia, Ver_Dia, OvalGfxInfo);

	Graph* pGr = pControl->getGraph();

	pGr->Addshape(pOVAL);
}

void opAddOval::Undo()
{
	Graph* pGr = pControl->getGraph();

	pGr->RemoveShape(pOVAL);
}

void opAddOval::Redo()
{
	Graph* pGr = pControl->getGraph();

	pGr->Addshape(pOVAL);
}
