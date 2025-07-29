#pragma once
#include "operations/operation.h"
class opMultiSelect:public operation
{
public:
    opMultiSelect(controller* pCont);
    virtual void Execute();
    virtual void Undo() {}    // selection changes aren't usually undone
    virtual void Redo() {}
};

