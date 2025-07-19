#include "opChangeFillCol.h"
#include"controller.h"
#include"GUI/GUI.h"

opChangeFillCol::opChangeFillCol(controller* pCont):operation(pCont)
{
}

void opChangeFillCol::Execute()
{
    GUI* pGUI = pControl->GetUI();
    PrevColor = pGUI->getCrntFillColor();

    int r, g, b;
    pGUI->PrintMessage("Enter R G B (0-255):");
    pGUI->enableFilling();
    r = stoi(pGUI->GetSrting());
    g = stoi(pGUI->GetSrting());
    b = stoi(pGUI->GetSrting());

    NewColor = color(r, g, b);
    pGUI->SetCrntFillColor(NewColor);
    pGUI->PrintMessage("Fill color updated.");
}

void opChangeFillCol::Undo()
{
    pControl->GetUI()->SetCrntFillColor(PrevColor);

}

void opChangeFillCol::Redo()
{
    pControl->GetUI()->SetCrntFillColor(NewColor);

}
