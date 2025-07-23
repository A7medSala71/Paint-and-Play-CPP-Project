#include"operations/opAddPol.h"
#include"Shapes/pol.h"
#include"GUI/GUI.h"
#include"controller.h"

opAddPol::opAddPol(controller* pCont):operation(pCont)
{
}

opAddPol::~opAddPol()
{
}

void opAddPol::Execute()
{
    // Get input/output interface
    GUI* pUI = pControl->GetUI();

    // Ask user for number of vertices
    pUI->PrintMessage("Enter number of vertices for the polygon:");
    string s = pUI->GetSrting();
    int numofvert = stoi(s);
    pUI->ClearStatusBar();

    // Allocate arrays for x and y coordinates
    int* arr_x = new int[numofvert];
    int* arr_y = new int[numofvert];

    // Get each vertex
    for (int i = 0; i < numofvert; i++)
    {
        string prompt = "Click on corner " + to_string(i + 1) + ":";
        pUI->PrintMessage(prompt);
        pUI->GetPointClicked(arr_x[i], arr_y[i]);
    }
    pUI->ClearStatusBar();

    // Prepare graphical info
    GfxInfo PolGfxInfo;
    PolGfxInfo.DrawClr = pUI->getCrntDrawColor();
    PolGfxInfo.BorderWdth = pUI->getCrntPenWidth();
    PolGfxInfo.isSelected = false;

    PolGfxInfo.isFilled = pUI->getIsFilled();
    if (PolGfxInfo.isFilled)
        PolGfxInfo.FillClr = pUI->getCrntFillColor();
    // Create shape and add it
    pPOL= new pol(numofvert, arr_x, arr_y, PolGfxInfo);
    Graph* pGr = pControl->getGraph();
    pGr->Addshape(pPOL);

    // Free temp arrays (they've been deep copied)
    delete[] arr_x;
    delete[] arr_y;

}

void opAddPol::Undo()
{
    Graph* pGr = pControl->getGraph();
    pGr->RemoveShape(pPOL);
}

void opAddPol::Redo()
{
    Graph* pGr = pControl->getGraph();
    pGr->Addshape(pPOL);
}
