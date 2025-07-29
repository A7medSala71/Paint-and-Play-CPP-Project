#pragma once
#include"operations/operation.h"
#include "Shapes/Shape.h"

class opPaste : public operation
{
private:
    shape* pastedShape;
public:
    opPaste(controller* pCont);
    virtual ~opPaste() {}
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
