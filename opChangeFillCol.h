#pragma once
#include"operations/operation.h"
class opChangeFillCol:public operation
{
private:
    color PrevColor, NewColor;
public:
    opChangeFillCol(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

