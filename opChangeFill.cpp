#include"operations/opChangeFill.h"
#include "GUI/GUI.h"
#include "Shapes/ColorPalette.h"
#include "Shapes/Graph.h"
#include "controller.h"

opChangeFill::opChangeFill(controller* pCont):operation(pCont)
{
	SelectedShape = nullptr;
}

void opChangeFill::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    SelectedShape = pGr->GetSelectedShape();
    if (!SelectedShape) {
        pUI->PrintMessage("No shape selected. Please select a shape first.");
        return;
    }

    // Store previous fill color & state
    OldColor = SelectedShape->getFillColor();
    OldFillState = SelectedShape->Isfilled();  // <-- NEW

    pUI->PrintMessage("Pick Fill color from palette.");

    ColorPalette palette;
    color picked = palette.PickColor();

    SelectedShape->ChngFillClr(picked);
    NewColor = picked;
    NewFillState = true;  // after execute shape is filled

    SelectedShape->SetSelected(false);
    pGr->SetSelectedShape(nullptr);

    pUI->PrintMessage("Fill color changed.");
}

void opChangeFill::Undo()
{
    if (SelectedShape) {
        SelectedShape->setFillColor(OldColor);
        SelectedShape->setIsFilled(OldFillState);  // restore old fill state
    }
}

void opChangeFill::Redo()
{
    if (SelectedShape) {
        SelectedShape->setFillColor(NewColor);
        SelectedShape->setIsFilled(NewFillState);  // apply new fill state again
    }
}
