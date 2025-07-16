#include "operations/OpAddLine.h"
#include "controller.h"
#include "Shapes/Line.h"
#include "GUI/GUI.h"


OpAddLine::OpAddLine(controller* pCont):operation(pCont)
{
}

OpAddLine::~OpAddLine()
{
}
void OpAddLine::Execute()
{
	Point P1, P2;
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Line: Click at first point");
	pUI->GetPointClicked(P1.x, P1.y);

	pUI->PrintMessage("Click at second point");
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	GfxInfo LinefxInfo;
	LinefxInfo.DrawClr = pUI->getCrntDrawColor();
	LinefxInfo.BorderWdth = pUI->getCrntPenWidth();
	LinefxInfo.isFilled = false;
	LinefxInfo.isSelected = false;

	pLine = new Line(P1, P2, LinefxInfo);
	Graph* pGr = pControl->getGraph();
	pGr->Addshape(pLine);
}

void OpAddLine::Redo()
{
	Graph* pGr = pControl->getGraph();
	pGr->Addshape(pLine);
}

void OpAddLine::Undo()
{
	Graph* pGr = pControl->getGraph();
	pGr->RemoveShape(pLine);
}

