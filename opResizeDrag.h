#pragma once
#include "operations/operation.h"
class opResizeDrag:public operation
{
public:
	opResizeDrag(controller* pCont) ;
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

