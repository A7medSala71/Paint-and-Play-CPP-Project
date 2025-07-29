#include "opResize.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
opResize::opResize(controller* pCont)
    : operation(pCont), SelectedShape(nullptr), Factor(1.0), ReverseFactor(1.0)
{
}

void opResize::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    SelectedShape = pGr->GetSelectedShape();
    if (!SelectedShape)
    {
        pUI->PrintMessage("No shape selected to resize!");
        return;
    }

    // --- Ask user for factor ---
    pUI->PrintMessage("Resize: (1) 1/4  (2) 1/2  (3) 2x  (4) 4x");
    char key;
    pUI->GetWindow()->WaitKeyPress(key);

    switch (key) {
    case '1': Factor = 0.25; break;
    case '2': Factor = 0.5;  break;
    case '3': Factor = 2.0;  break;
    case '4': Factor = 4.0;  break;
    default:
        pUI->PrintMessage("Invalid factor selected");
        return;
    }
    ReverseFactor = 1.0 / Factor;
    SelectedShape->Resize(Factor);

    pUI->PrintMessage("Shape resized by factor " + to_string(Factor));

}

void opResize::Undo()
{
    if (SelectedShape)
        SelectedShape->Resize(ReverseFactor);
}

void opResize::Redo()
{
    if (SelectedShape)
        SelectedShape->Resize(Factor);
}