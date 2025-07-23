#include"operations/opAddSqr.h"
#include"Square.h"
#include"controller.h"
opAddSqr::opAddSqr(controller* pCont): operation(pCont)
{
}

opAddSqr::~opAddSqr()
{
}

void opAddSqr::Execute()
{
	Point P1;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Square: Click at Center");
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	pUI->PrintMessage(msg);

	pUI->PrintMessage("Enter Side Length");
	string s = pUI->GetSrting();
	int side = stoi(s);
	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo SquareGfxInfo;

	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pUI->getCrntDrawColor();
	SquareGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	SquareGfxInfo.isSelected = false;	//defualt is not selected
	SquareGfxInfo.isFilled = pUI->getIsFilled();
	if (SquareGfxInfo.isFilled)
		SquareGfxInfo.FillClr = pUI->getCrntFillColor();


	pSqr = new Square(P1, side, SquareGfxInfo);

	Graph* pGr = pControl->getGraph();

	pGr->Addshape(pSqr);
}

void opAddSqr::Undo()
{
	Graph* pGr = pControl->getGraph();
	pGr->RemoveShape(pSqr);
}

void opAddSqr::Redo()
{
	Graph* pGr = pControl->getGraph();
	pGr->Addshape(pSqr);
}
