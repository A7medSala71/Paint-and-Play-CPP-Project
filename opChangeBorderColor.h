#pragma once
#include"operations/operation.h"
#include"Shapes/Shape.h"
class opChangeBorderColor:public operation
{
private:
    shape* SelectedShape;
    color OldColor, NewColor;
public:
    opChangeBorderColor(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

