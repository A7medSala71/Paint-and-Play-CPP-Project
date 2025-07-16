#pragma once
#include"operation.h"
#include"../Square.h"
class opAddSqr: public operation
{
private:
	Square* pSqr;
public:
	opAddSqr(controller* pCont);
	virtual ~opAddSqr();

	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

