#include "operations/opSelect.h"
#include"Shapes/Graph.h"
#include"GUI/GUI.h"
#include"controller.h"

opSelect::opSelect(controller* pCont):operation(pCont)
{
    oldSelection = nullptr;
    newSelection = nullptr;
}

opSelect::~opSelect()
{
}

void opSelect::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();

    int x, y;
    pUI->PrintMessage("Click on a shape to select or empty space to unselect all.");
    pUI->GetPointClicked(x, y);

    // Store previous selection for undo
    oldSelection = pGraph->GetSelectedShape();

    // Find shape under click
    shape* clickedShape = pGraph->Getshape(x, y);

    if (clickedShape) {
        // Deselect all others
        pGraph->UnselectAll();

        // Select clicked shape
        pGraph->SetSelectedShape(clickedShape);

        // Display info
        string info = clickedShape->GetInfo();
        pUI->PrintMessage("Selected: " + info);
    }
    else {
        // Clicked empty area ? clear selection
        pGraph->UnselectAll();
        pGraph->SetSelectedShape(nullptr);
        pUI->PrintMessage("No shape selected.");
    }

    // Save new selection for redo
    newSelection = clickedShape;

    pControl->UpdateInterface();
}

void opSelect::Undo()
{
    Graph* pGraph = pControl->getGraph();
    pGraph->SetSelectedShape(oldSelection);           // Restore old selection
}

void opSelect::Redo()
{
    Graph* pGraph = pControl->getGraph();
    pGraph->SetSelectedShape(newSelection);           // Reapply new selection
}
