#include"operations/opAddRegPol.h"
#include"Shapes/RegPol.h"
#include"GUI/GUI.h"
#include"controller.h"

opAddRegPol::opAddRegPol(controller* pCont):operation(pCont)
{
}

opAddRegPol::~opAddRegPol()
{
}

void opAddRegPol::Execute()
{

    // Get input/output interface
    GUI* pUI = pControl->GetUI();
    // Ask user for number of vertices
    pUI->PrintMessage("Enter number of sides of polygon:");
    string s = pUI->GetSrting();
    int numofsides = stoi(s);
    if (numofsides < 3)
    {
        pUI->PrintMessage("polygon must have at least 3 sides.");
        return;
    }
    Point center, RadPT;

    pUI->PrintMessage("Regular Polygon: Click the center point");
    pUI->GetPointClicked(center.x, center.y);

    pUI->PrintMessage("Click a point on the perimeter (defines radius)");
    pUI->GetPointClicked(RadPT.x, RadPT.y);

    pUI->ClearStatusBar();

    // Prepare graphical info
    GfxInfo RegPolGfxInfo;
    RegPolGfxInfo.DrawClr = pUI->getCrntDrawColor();
    RegPolGfxInfo.BorderWdth = pUI->getCrntPenWidth();
    RegPolGfxInfo.isSelected = false;

    RegPolGfxInfo.isFilled = pUI->getIsFilled();
    if (RegPolGfxInfo.isFilled)
        RegPolGfxInfo.FillClr = pUI->getCrntFillColor();
    // Create shape and add it
    pRPol = new RegPol(center, RadPT, numofsides, RegPolGfxInfo);
    Graph* pGr = pControl->getGraph();
    pGr->Addshape(pRPol);
}

void opAddRegPol::Undo()
{
    Graph* pGr = pControl->getGraph();
    pGr->RemoveShape(pRPol);
}

void opAddRegPol::Redo()
{
    Graph* pGr = pControl->getGraph();
    pGr->Addshape(pRPol);
}
