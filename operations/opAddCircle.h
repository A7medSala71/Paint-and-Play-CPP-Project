#pragma once
#include"../operations/operation.h"
#include"../Shapes/Circle.h"
class opAddCircle:public operation
{
private:
	Circle* pCirc;
public:
	opAddCircle(controller* pCont);
	virtual ~opAddCircle();

	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

};

