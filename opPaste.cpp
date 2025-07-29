#include "opPaste.h"
#include "controller.h"
#include "GUI/GUI.h"

opPaste::opPaste(controller* pCont) : operation(pCont) 
{
    pastedShape = nullptr;
}

void opPaste::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();
    if (!pControl->getClipboardShape())
    {
        pUI->PrintMessage("Clipboard is empty!");
        return;
    }
    Point pastePoint;
    pUI->PrintMessage("Click point to paste shape");
    pUI->GetPointClicked(pastePoint.x, pastePoint.y);
    // Clone shape from clipboard
    pastedShape = pControl->getClipboardShape()->Clone();
    pastedShape->Move(pastePoint);


    // Add shape to graph
    pGr->Addshape(pastedShape);

    pUI->PrintMessage("Shape pasted.");
}

void opPaste::Undo()
{
    if (pastedShape)
    {
        pControl->getGraph()->RemoveShape(pastedShape);

    }
}

void opPaste::Redo()
{
    if (pastedShape)
    {
        pControl->getGraph()->Addshape(pastedShape);

    }
}
