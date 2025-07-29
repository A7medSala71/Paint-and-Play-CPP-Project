#include "opZoomOut.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"

opZoomOut::opZoomOut(controller* pCont) : operation(pCont), factor(0.8), reverseFactor(1.0 / 0.8) {}

void opZoomOut::Execute()
{
    GUI* pUI = pControl->GetUI();
    pUI->PrintMessage("Click a point to Zoom out around");
    pUI->GetPointClicked(ref.x, ref.y);

    pControl->getGraph()->Zoom(factor, ref);
    pUI->PrintMessage("Zoomed Out");
}

void opZoomOut::Undo()
{
    pControl->getGraph()->Zoom(reverseFactor, ref);
}

void opZoomOut::Redo()
{
    pControl->getGraph()->Zoom(factor, ref);
}