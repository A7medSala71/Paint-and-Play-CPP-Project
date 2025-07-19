#include "opAddRect.h"
#include "..\shapes\Rect.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddRect::opAddRect(controller * pCont):operation(pCont)
{
	pRect = nullptr;
}
opAddRect::~opAddRect()
{
		pRect = nullptr;
} 

//Execute the operation
void opAddRect::Execute() 
{
	Point P1, P2;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Rectangle: Click at first corner");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at second corner";
	pUI->PrintMessage(msg);
	//Read 2nd corner and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo RectGfxInfo;
	
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pUI->getCrntDrawColor();
	RectGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	RectGfxInfo.isSelected = false;	//defualt is not selected

	RectGfxInfo.isFilled = pUI->getIsFilled();
	if (RectGfxInfo.isFilled)
		RectGfxInfo.FillClr = pUI->getCrntFillColor();


	//Create a rectangle with the above parameters
	pRect=new Rect(P1, P2, RectGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the rectangle to the list of shapes
	pGr->Addshape(pRect);

	pUI->PrintMessage("Do you want to stick an image to this shape? (y/n)");
	string answer = pUI->GetSrting();

	if (answer == "y" || answer == "Y") {
		pUI->PrintMessage("Enter image path: ");
		string path = pUI->GetSrting();
		pRect->setImagePath(path);
		pUI->PrintMessage("Image successfully attached.");
	}

}

void opAddRect::Undo()
{
	Graph* pGr = pControl->getGraph();

	pGr->RemoveShape(pRect);
}

void opAddRect::Redo()
{
	Graph* pGr = pControl->getGraph();

	pGr->Addshape(pRect);
}
