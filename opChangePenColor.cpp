#include "opChangePenColor.h"
#include"GUI/GUI.h"
#include"controller.h"

opChangePenColor::opChangePenColor(controller* pCont):operation(pCont)
{

}

void opChangePenColor::Execute()
{
    GUI* pGUI = pControl->GetUI();
    OldColor = pGUI->getCrntDrawColor();

    int r, g, b;
    pGUI->PrintMessage("Enter R G B (0-255):");
    r = stoi(pGUI->GetSrting());
    g = stoi(pGUI->GetSrting());
    b = stoi(pGUI->GetSrting());

    NewColor = color(r, g, b);
    pGUI->SetCrntDrawColor(NewColor);
    pGUI->PrintMessage("Pen color updated.");
}

void opChangePenColor::Undo()
{
    pControl->GetUI()->SetCrntDrawColor(OldColor);

}

void opChangePenColor::Redo()
{
    pControl->GetUI()->SetCrntDrawColor(NewColor);

}
