#pragma once
#include"operation.h"
#include"../Shapes/pol.h"
class opAddPol:public operation
{
private:
	pol* pPOL;
public:
	opAddPol(controller* pCont);
	virtual ~opAddPol();

	virtual void Execute();
	virtual void Undo();
	virtual void Redo();


};

