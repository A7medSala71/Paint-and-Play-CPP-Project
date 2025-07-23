#include "opColorPalette.h"
#include"..\Shapes\ColorPalette.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opColorPalette::opColorPalette(controller* pCont) : operation(pCont) {}

void opColorPalette::Execute() {
    GUI* pUI = pControl->GetUI();
    ColorPalette palette;
    color chosenColor = palette.PickColor();

    pUI->PrintMessage("Apply to: 1) Pen Color or 2) Fill Color?");
    string choice = pUI->GetSrting();

    if (choice == "1") {
        IsFillChange = false;
        PrevColor = pUI->getCrntDrawColor();
        NewColor = chosenColor;
        pUI->SetCrntDrawColor(NewColor);
        pUI->PrintMessage("Pen color updated.");
    }
    else if (choice == "2") {
        IsFillChange = true;
        PrevColor = pUI->getCrntFillColor();
        PrevFillMode = pUI->getIsFilled();

        NewColor = chosenColor;
        NewFillMode = true;   // always fill when choosing fill color
        pUI->SetCrntFillColor(NewColor);
        pUI->enableFilling();
        pUI->PrintMessage("Fill color updated.");
    }
    else {
        pUI->PrintMessage("Invalid choice. No change applied.");
    }
}

void opColorPalette::Undo()
{
    GUI* pUI = pControl->GetUI();
    if (IsFillChange) {
        pUI->SetCrntFillColor(PrevColor);
        pUI->setIsFilled(PrevFillMode);
    }
    else {
        pUI->SetCrntDrawColor(PrevColor);
    }
}

void opColorPalette::Redo()
{
    GUI* pUI = pControl->GetUI();
    if (IsFillChange) {
        pUI->SetCrntFillColor(NewColor);
        pUI->setIsFilled(NewFillMode);
    }
    else {
        pUI->SetCrntDrawColor(NewColor);
    }
}

