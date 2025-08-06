#include "opCopy.h"
#include "controller.h"
#include "GUI/GUI.h"

opCopy::opCopy(controller* pCont) : operation(pCont) {}

opCopy::~opCopy()
{
}

void opCopy::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();

    shape* selected = pGraph->GetSelectedShape();
    if (!selected)
    {
        pUI->PrintMessage("No shape selected to copy");
        return;
    }
    
    // store in clipboard
    pControl->setClipboardShape(selected);
    pUI->PrintMessage("Shape copied to clipboard");
}

void opCopy::Undo()
{
}

void opCopy::Redo()
{
}
