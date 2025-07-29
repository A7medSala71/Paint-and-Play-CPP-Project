#include "operations/opSave.h"

#include "controller.h"
#include "GUI/GUI.h"
opSave::opSave(controller* pCont) : operation(pCont) {}

void opSave::ReadOperationParameters()
{
    pGUI = pControl->GetUI();
    pGUI->PrintMessage("Please, Enter a file name then press enter: ");
    Name = pGUI->GetSrting() + ".txt";

    outFile.open(Name);
    while (outFile.fail())
    {
        pGUI->PrintMessage("Invalid name, please try again:");
        Name = pGUI->GetSrting() + ".txt";
        outFile.open(Name);
    }
}

void opSave::Execute()
{
    ReadOperationParameters();

    if (outFile.is_open())
    {
        pGraph = pControl->getGraph();
        pGraph->SaveShapes(outFile, pGUI);
        pGUI->PrintMessage("Drawing SAVED successfully.");
        outFile.close();
    }
    else
    {
        pGUI->PrintMessage("Failed to open file for saving!");
    }
}

void opSave::Undo() {}
void opSave::Redo() {}