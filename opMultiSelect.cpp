#include "opMultiSelect.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "shapes/Graph.h"

opMultiSelect::opMultiSelect(controller* pCont) : operation(pCont) {}

void opMultiSelect::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    pUI->PrintMessage("Multi-Select: Click shapes to select, click empty area to exit.");

    while (true)
    {
        int x, y;
        pUI->GetPointClicked(x, y);

        shape* clickedShape = pGr->Getshape(x, y);
        if (!clickedShape)
        {
            pUI->PrintMessage("Multi-selection ended");
            break;
        }

        // Toggle selection state
        if (pGr->IsShapeSelected(clickedShape))
        {
            pGr->RemoveFromSelection(clickedShape);
            pUI->PrintMessage("Shape unselected");
        }
        else
        {
            pGr->AddToSelection(clickedShape);
            pUI->PrintMessage("Shape selected");
        }

        pGr->Draw(pUI);
    }
}
