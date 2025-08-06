#include "opResizeDrag.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
    

opResizeDrag::opResizeDrag(controller* pCont) : operation(pCont) {}

void opResizeDrag::Execute() {
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();

    int x, y;
    pUI->PrintMessage("Click on a shape to resize.");
    pUI->GetPointClicked(x, y);

    shape* selectedShape = pGraph->Getshape(x, y);
    if (!selectedShape) {
        pUI->PrintMessage("No shape selected for resizing.");
        return;
    }

    pUI->PrintMessage("Press and hold the left mouse button to resize, release to finish.");

    int xPrev = x, yPrev = y;
    bool isPressed = false;

    // Wait until mouse button is pressed (user starts dragging)
    do {
        pUI->GetMouseState(x, y, isPressed);
    } while (!isPressed);

    // Start dragging
    while (isPressed) {
        pUI->GetMouseState(x, y, isPressed);

        double dx = x - xPrev;
        double factor = 1.0 + dx * 0.01;
        if (factor < 0.1) factor = 0.1;

        selectedShape->Resize(factor);
        xPrev = x;
        yPrev = y;

        pControl->UpdateInterface();
    }

    pUI->PrintMessage("Resize complete.");
}

void opResizeDrag::Undo() {}
void opResizeDrag::Redo() {}
