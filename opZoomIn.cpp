#include "opZoomIn.h"
#include "controller.h"
#include "GUI/GUI.h"
#include"Shapes/Graph.h"
opZoomIn::opZoomIn(controller* pCont) : operation(pCont), factor(1.25), reverseFactor(1.0 / 1.25) {}

void opZoomIn::Execute()
{
    GUI* pUI = pControl->GetUI();
    pUI->PrintMessage("Click a point to Zoom In around");
    pUI->GetPointClicked(ref.x, ref.y);

    pControl->getGraph()->Zoom(factor, ref);
    pUI->PrintMessage("Zoomed In");
}

void opZoomIn::Undo()
{
    pControl->getGraph()->Zoom(reverseFactor, ref);
}

void opZoomIn::Redo()
{
    pControl->getGraph()->Zoom(factor, ref);
}
