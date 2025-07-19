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
    pUI->PrintMessage("Click on a shape to select or click empty space to unselect all.");
    pUI->GetPointClicked(x, y);

    shape* selected = pGraph->Getshape(x, y);

    oldSelection = pGraph->GetSelectedShape();        // Save current selection
    newSelection = pGraph->Getshape(x, y);            // Try selecting new shape
    pGraph->SetSelectedShape(newSelection);           // Update selection in Graph
    if (selected) {
        pGraph->UnselectAll();
        selected->SetSelected(true);

        // Display shape info
        string info = selected->GetInfo();
        pUI->PrintMessage("Selected: " + info);
    }
    else {
        pGraph->UnselectAll();
        pUI->PrintMessage("No shape selected.");
    }

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
