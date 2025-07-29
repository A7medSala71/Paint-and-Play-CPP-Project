#pragma once
#include "operations/operation.h"
#include "Shapes/Shape.h"

class opSendToBack : public operation
{
private:
    shape* SelectedShape;
    int OldIndex;

public:
    opSendToBack(controller* pCont);
    virtual ~opSendToBack();

    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
