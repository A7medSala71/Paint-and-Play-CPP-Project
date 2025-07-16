#pragma once
#include "operation.h"
#include"../Shapes/Line.h"
class OpAddLine:public operation
{
private:
	Line* pLine;
public:
	OpAddLine(controller* pCont);
	virtual ~OpAddLine();

	virtual void Execute();
	virtual void Redo();
	virtual void Undo();

};

