#include "controller.h"
#include "operations\opAddRect.h"
#include "operations/OpAddLine.h"
#include"opAddTri.h"
#include"operations/opAddSqr.h"
#include"operations/opAddCircle.h"
#include"operations/opAddOval.h"
#include"operations/opAddPol.h"
#include"operations/opAddRegPol.h"
#include"operations/opSelect.h"
#include"opChangePenColor.h"
#include"opChangeFillCol.h"


//Constructor
controller::controller()
{
	pGraph = new Graph;
	pGUI = new GUI;	//Create GUI object
}

//==================================================================================//
//								operations-Related Functions							//
//==================================================================================//
operationType controller::GetUseroperation() const
{
	//Ask the input to get the operation from the user.
	return pGUI->GetUseroperation();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an operation and executes it
operation* controller::createOperation(operationType OpType)
{
	operation* pOp = nullptr;
	
	//According to operation Type, create the corresponding operation object
	switch (OpType)
	{
		case DRAW_RECT:
			pOp = new opAddRect(this);
			break;

		case DRAW_LINE:
			pOp = new OpAddLine(this);
			break;
		case DRAW_TRI:
			pOp = new opAddTri(this);
			break;
		case DRAW_Sqr:
			pOp = new opAddSqr(this);
			break;
		case DRAW_CIRC:
			pOp = new opAddCircle(this);
			break;
		case Draw_Oval:
			pOp = new opAddOval(this);
			break;
		case Draw_Pol:
			pOp = new opAddPol(this);
			break;
		case Draw_RegPol:
			pOp = new opAddRegPol(this);
			break;
		case Select_Shape:
			pOp = new opSelect(this);
			break;
		case CHNG_DRAW_CLR:
			pOp = new opChangePenColor(this);
			break;
		case CHNG_FILL_CLR:
			pOp = new opChangeFillCol(this);
			break;

		case EXIT:
			///create Exitoperation here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no operation
			break;
	}

	return pOp;
	
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all shapes on the user interface
void controller::UpdateInterface() const
{	
	pGraph->Draw(pGUI);
}
void controller::Undo()
{
	if (Undo_Stack.empty())
		return;
	else {
		operation* op = Undo_Stack.top();
		Undo_Stack.pop();
		op->Undo();
		Redo_Stack.push(op);
	}
}
void controller::Redo()
{
	if (Redo_Stack.empty())
		return;
	else {
		operation* op = Redo_Stack.top();
		Redo_Stack.pop();
		op->Redo();
		Undo_Stack.push(op);
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the UI
GUI *controller::GetUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the Graph
Graph* controller::getGraph() const
{
	return pGraph;
}



//Destructor
controller::~controller()
{
	delete pGUI;
	delete pGraph;
	
}



//==================================================================================//
//							Run function											//
//==================================================================================//
void controller::Run()
{
	operationType OpType;
	do
	{
		//1. Ask the GUI to read the required operation from the user
		OpType = GetUseroperation();

		if (OpType == UNDO) {
			Undo();
		}
		else if (OpType == REDO) {
			Redo();
		}
		else {
			//2. Create an operation coresspondingly
			operation* pOpr = createOperation(OpType);

			//3. Execute the created operation
			if (pOpr)
			{
				pOpr->Execute();
				Undo_Stack.push(pOpr);

				// Clear Redo stack (no longer valid)
				while (!Redo_Stack.empty()) {
					delete Redo_Stack.top();
					Redo_Stack.pop();
				}
			}
		}

		//4. Update the interface
		UpdateInterface();

	} while (OpType != EXIT);

}