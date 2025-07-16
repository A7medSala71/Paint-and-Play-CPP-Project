#include"operations/opAddTri.h"
#include"Shapes/Tri.h"
#include"GUI/GUI.h"
#include"controller.h"

opAddTri::opAddTri(controller* pCont):operation(pCont)
{
}

opAddTri::~opAddTri()
{
}

void opAddTri::Execute()
{

	Point P1, P2,P3;

	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Triangle: Click at first corner");
	pUI->GetPointClicked(P1.x, P1.y);
	string msg1 = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg1 += " ... Click at second corner";
	pUI->PrintMessage(msg1);
	pUI->GetPointClicked(P2.x, P2.y);
	string msg2 = "Second corner is at (" + to_string(P2.x) + ", " + to_string(P2.y) + " )";
	msg2 += " ... Click at Third corner";
	pUI->PrintMessage(msg2);
	pUI->GetPointClicked(P3.x, P3.y);
	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo TriGfxInfo;

	//get drawing, filling colors and pen width from the interface
	TriGfxInfo.DrawClr = pUI->getCrntDrawColor();
	TriGfxInfo.FillClr = pUI->getCrntFillColor();
	TriGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	TriGfxInfo.isFilled = false;	//default is not filled
	TriGfxInfo.isSelected = false;	//defualt is not selected


	//Create a rectangle with the above parameters
	pTRI= new Tri(P1, P2, P3, TriGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the rectangle to the list of shapes
	pGr->Addshape(pTRI);

	pUI->PrintMessage("Do you want to stick an image to this shape? (y/n)");
	string answer = pUI->GetSrting();

	if (answer == "y" || answer == "Y") {
		pUI->PrintMessage("Enter image path: ");
		string path = pUI->GetSrting();
		pTRI->setImagePath(path);
		pUI->PrintMessage("Image successfully attached.");
	}

}

void opAddTri::Undo()
{
	Graph* pGr = pControl->getGraph();

	pGr->RemoveShape(pTRI);
}

void opAddTri::Redo()
{
	Graph* pGr = pControl->getGraph();

	pGr->Addshape(pTRI);
}

