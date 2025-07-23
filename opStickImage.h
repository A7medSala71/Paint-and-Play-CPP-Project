#pragma once
#include "operations/operation.h"
#include "Shapes/Shape.h"

class opStickImage : public operation
{
private:
	shape* SelectedShape;
	string PrevImagePath;
	string NewImagePath;

public:
	opStickImage(controller* pCont);
	virtual ~opStickImage();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
