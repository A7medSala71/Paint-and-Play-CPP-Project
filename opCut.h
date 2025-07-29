#pragma once
#include "operations/operation.h"
#include "Shapes/Shape.h"

class opCut : public operation
{
    shape* CutShape = nullptr;    // pointer to cut shape (ownership moved)
    int RemovedIndex;             // index where it was removed
public:
    opCut(controller* pCont);
    virtual ~opCut();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
