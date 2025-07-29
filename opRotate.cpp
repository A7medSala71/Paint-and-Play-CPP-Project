#include "operations/opRotate.h"
#include "controller.h"
#include "GUI/GUI.h"
#include"Shapes/pol.h"
opRotate::opRotate(controller* pCont) : operation(pCont), SelectedShape(nullptr) {}

void opRotate::Execute() {
    Graph* pGraph = pControl->getGraph();
    GUI* pUI = pControl->GetUI();

    SelectedShape = pGraph->GetSelectedShape();
    if (!SelectedShape) {
        pUI->PrintMessage("No shape selected to rotate!");
        return;
    }

    // Skip irregular polygon
    if (dynamic_cast<pol*>(SelectedShape)) {
        pUI->PrintMessage("Irregular polygon rotation not supported!");
        return;
    }

    SelectedShape->Rotate();
    pUI->PrintMessage("Shape rotated by 90 degrees");
}

void opRotate::Undo() {
    if (SelectedShape) {
        // Rotate back by 270 = -90
        for (int i = 0; i < 3; i++) SelectedShape->Rotate();
    }
}

void opRotate::Redo() {
    if (SelectedShape) {
        SelectedShape->Rotate();
    }
}
