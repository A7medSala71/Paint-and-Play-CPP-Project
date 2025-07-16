#pragma once
#include"operation.h"
#include"../Shapes/Oval.h"
class opAddOval:public operation
{
private:
	Oval* pOVAL;
public:
	opAddOval(controller* pCont);
	virtual ~opAddOval();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

};

