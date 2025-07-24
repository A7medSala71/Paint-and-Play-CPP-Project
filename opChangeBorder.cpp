#include"operations/opChangeBorder.h"
#include "controller.h"
#include "GUI/GUI.h"
#include"Shapes/ColorPalette.h"
opChangeBorder::opChangeBorder(controller* pCont):operation(pCont)
{
	SelectedShape = nullptr;
}
void opChangeBorder::Execute() {
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();
    ColorPalette* pColorPal = nullptr;

    SelectedShape = pGr->GetSelectedShape();
    if (!SelectedShape) {
        pUI->PrintMessage("No shape selected. Please select a shape first.");
        return;
    }

    OldColor = SelectedShape->getBorderColor();
    pUI->PrintMessage("Pick border color from palette.");
    color picked =pColorPal->PickColor();  // reuse color palette
    SelectedShape->setBorderColor(picked);
    NewColor = picked;
    pUI->PrintMessage("Border color changed.");
}

void opChangeBorder::Undo()
{
}

void opChangeBorder::Redo()
{
}
