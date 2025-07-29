#pragma once
#include"operations/operation.h"
#include "Shapes/Shape.h"

class opResize : public operation
{
private:
    shape* SelectedShape;
    double Factor;
    double ReverseFactor;

public:
    opResize(controller* pCont);

    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
