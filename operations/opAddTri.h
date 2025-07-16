#pragma once
#include"operation.h"
#include"../Shapes/Tri.h"
class opAddTri:public operation
{
private:
	Tri* pTRI;
public:
	opAddTri(controller* pCont);
	virtual ~opAddTri();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

