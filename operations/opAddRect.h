#pragma once
#include "operation.h"
#include"../Shapes/Rect.h"
//Add Rectangle operation class
class opAddRect: public operation
{
private:
	Rect* pRect;
public:
	opAddRect(controller *pCont);
	virtual ~opAddRect();
	
	//Add rectangle to the controller
	virtual void Execute() ;
	virtual void Undo();
	virtual void Redo();
};

