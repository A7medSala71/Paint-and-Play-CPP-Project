#include "opCut.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Shape.h"
opCut::opCut(controller* pCont) : operation(pCont), CutShape(nullptr), RemovedIndex(-1) {}
opCut::~opCut() {}

void opCut::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    shape* Selected = pGr->GetSelectedShape();
    if (!Selected) {
        pUI->PrintMessage("No shape selected to cut!");
        return;
    }

    // Copy to controller buffer
    pControl->setClipboardShape(Selected->Clone());

    // Save index before removing
    RemovedIndex = pGr->GetShapeIndex(Selected);

    // Remove from graph but keep pointer
    CutShape = Selected;
    pGr->RemoveShape(CutShape);

    pUI->PrintMessage("Shape cut and copied to clipboard");
}

void opCut::Undo()
{
    if (CutShape) {
        pControl->getGraph()->InsertShapeAt(CutShape, RemovedIndex);
        pControl->GetUI()->PrintMessage("Undo Cut");
    }
}

void opCut::Redo()
{
    if (CutShape) {
        pControl->getGraph()->RemoveShape(CutShape);
        pControl->GetUI()->PrintMessage("Redo Cut");
    }
}
