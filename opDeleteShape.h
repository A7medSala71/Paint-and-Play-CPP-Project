#pragma once
#include "operations/operation.h"
#include "Shapes/shape.h"
class opDeleteShape:public operation
{
private:
    shape* DeletedShape;  // pointer to the deleted shape
    int DeletedIndex;     // index of shape in Graph list 
public:
    opDeleteShape(controller* pCont);

    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

