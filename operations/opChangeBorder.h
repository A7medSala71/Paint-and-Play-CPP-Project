#pragma once
#include"operation.h"
#include"../Shapes/Shape.h"
class opChangeBorder : public operation
{
private:
    shape* SelectedShape;
    color OldColor, NewColor;
public:
    opChangeBorder(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

