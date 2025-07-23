#include"opStickImage.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Shape.h"

opStickImage::opStickImage(controller* pCont) : operation(pCont)
{
	SelectedShape = nullptr;
}

opStickImage::~opStickImage() {}

void opStickImage::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	SelectedShape = pGr->GetSelectedShape();

	if (SelectedShape)
	{
		PrevImagePath = SelectedShape->getImagePath();
		pUI->PrintMessage("Enter image path to stick: ");
		NewImagePath = pUI->GetSrting();

		SelectedShape->setImagePath(NewImagePath);
		pUI->PrintMessage("Image successfully attached.");
	}
	else
	{
		pUI->PrintMessage("No shape selected. Please select a shape first.");
	}
}

void opStickImage::Undo()
{
	if (SelectedShape)
		SelectedShape->setImagePath(PrevImagePath);
}

void opStickImage::Redo()
{
	if (SelectedShape)
		SelectedShape->setImagePath(NewImagePath);
}
