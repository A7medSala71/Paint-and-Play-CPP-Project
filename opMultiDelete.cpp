#include "opMultiDelete.h"
#include "controller.h"
#include "Shapes/Graph.h"
#include "GUI/GUI.h"

opMultiDelete::opMultiDelete(controller* pCont) : operation(pCont) {}

void opMultiDelete::Execute()
{
    Graph* pGr = pControl->getGraph();
    GUI* pUI = pControl->GetUI();

    auto selectedShapes = pGr->GetSelectedShapes();
    if (selectedShapes.empty())
    {
        pUI->PrintMessage("No shapes selected for deletion");
        return;
    }

    deletedShapes = selectedShapes; // Save for undo

    for (auto* s : selectedShapes)
        pGr->RemoveShape(s);

    pGr->ClearSelection();
    pUI->PrintMessage("All selected shapes deleted");
}

void opMultiDelete::Undo()
{
    Graph* pGr = pControl->getGraph();
    for (auto* s : deletedShapes)
        pGr->Addshape(s);
    pControl->GetUI()->PrintMessage("Undo Multi Delete");
}

void opMultiDelete::Redo()
{
    Graph* pGr = pControl->getGraph();
    for (auto* s : deletedShapes)
        pGr->RemoveShape(s);
    pControl->GetUI()->PrintMessage("Redo Multi Delete");
}
