#include "opChangeBorderColor.h"
#include "GUI/GUI.h"
#include "Shapes/ColorPalette.h"
#include "Shapes/Graph.h"
#include "controller.h"

opChangeBorderColor::opChangeBorderColor(controller* pCont) : operation(pCont)
{
    SelectedShape = nullptr;
}

void opChangeBorderColor::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    SelectedShape = pGr->GetSelectedShape();
    if (!SelectedShape) {
        pUI->PrintMessage("No shape selected. Please select a shape first.");
        return;
    }

    OldColor = SelectedShape->getBorderColor();
    pUI->PrintMessage("Pick border color from palette.");

    ColorPalette palette;  // same way as opColorPalette
    color picked = palette.PickColor();

    SelectedShape->setBorderColor(picked);
    NewColor = picked;
    SelectedShape->SetSelected(false);
    pGr->SetSelectedShape(nullptr);
    pUI->PrintMessage("Border color changed.");
}

void opChangeBorderColor::Undo() {
    if (SelectedShape) SelectedShape->setBorderColor(OldColor);
}

void opChangeBorderColor::Redo() {
    if (SelectedShape) SelectedShape->setBorderColor(NewColor);
}
