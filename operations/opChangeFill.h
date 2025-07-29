#pragma once
#include"operation.h"
#include"../Shapes/Shape.h"
class opChangeFill:public operation
{
private:
    shape* SelectedShape;
    color OldColor, NewColor;
    bool OldFillState;
    bool NewFillState;
public:
    opChangeFill(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

