#pragma once
#include"operations/operation.h"
#include "Shapes/Shape.h"

class opCopy : public operation
{
public:
    opCopy(controller* pCont);
    virtual ~opCopy();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
