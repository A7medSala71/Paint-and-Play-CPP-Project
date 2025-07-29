#include "opLoad.h"
#include "controller.h"
#include "GUI/GUI.h"
#include <fstream>

opLoad::opLoad(controller* pCont) : operation(pCont) {}

void opLoad::ReadOperationParameters()
{
    GUI* pUI = pControl->GetUI();
    pUI->PrintMessage("Enter file name to load (without extension): ");
    fileName = pUI->GetSrting() + ".txt";
}

void opLoad::Execute()
{
    ReadOperationParameters();
    ifstream inFile(fileName);
    GUI* pUI = pControl->GetUI();

    if (!inFile.is_open()) {
        pUI->PrintMessage("Could not open file: " + fileName);
        return;
    }

    Graph* pGraph = pControl->getGraph();
    pGraph->LoadShapes(inFile, pUI);
    inFile.close();

    pUI->PrintMessage("Graph loaded successfully!");
}

void opLoad::Undo() {}
void opLoad::Redo() {}
