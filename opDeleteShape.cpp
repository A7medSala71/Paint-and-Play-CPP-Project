#include "opDeleteShape.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
opDeleteShape::opDeleteShape(controller* pCont):operation(pCont)
{
	DeletedShape = nullptr;
	DeletedIndex = -1;
}
void opDeleteShape::Execute()
{
    Graph* pGr = pControl->getGraph();
    GUI* pUI = pControl->GetUI();

    shape* selectedShape = pGr->GetSelectedShape();
    if (!selectedShape)
    {
        pUI->PrintMessage("No shape selected to delete.");
        return;
    }

    // store shape and its position before deleting
    DeletedShape = selectedShape;
    DeletedIndex = pGr->GetShapeIndex(DeletedShape);

    // remove from list
    pGr->RemoveShape(DeletedShape);

    // clear selection
    pGr->SetSelectedShape(nullptr);

    pUI->PrintMessage("Shape deleted.");
}

void opDeleteShape::Undo()
{
    if (DeletedShape)
    {
        Graph* pGr = pControl->getGraph();
        // add shape back to the same position
        pGr->InsertShapeAt(DeletedShape, DeletedIndex);
    }
}

void opDeleteShape::Redo()
{
    if (DeletedShape)
    {
        Graph* pGr = pControl->getGraph();
        pGr->RemoveShape(DeletedShape);
    }
}