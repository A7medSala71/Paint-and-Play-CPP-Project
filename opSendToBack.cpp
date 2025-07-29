#include "opSendToBack.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
opSendToBack::opSendToBack(controller* pCont) : operation(pCont)
{
    SelectedShape = nullptr;
    OldIndex = -1;
}

opSendToBack::~opSendToBack() {}

void opSendToBack::Execute()
{
    Graph* pGr = pControl->getGraph();
    GUI* pUI = pControl->GetUI();

    SelectedShape = pGr->GetSelectedShape();
    if (!SelectedShape)
    {
        pUI->PrintMessage("No shape selected to send to back.");
        return;
    }

    OldIndex = pGr->GetShapeIndex(SelectedShape);
    pGr->SendToBack(SelectedShape);
    pUI->PrintMessage("Shape sent to back.");
}

void opSendToBack::Undo()
{
    if (SelectedShape && OldIndex != -1)
    {
        Graph* pGr = pControl->getGraph();

        // Remove from index 0 (it was moved to back)
        pGr->RemoveShape(SelectedShape);

        // Insert it back to its old position
        pGr->InsertShapeAt(SelectedShape, OldIndex);
    }
}

void opSendToBack::Redo()
{
    Graph* pGr = pControl->getGraph();
    if (SelectedShape)
        pGr->SendToBack(SelectedShape);
}
