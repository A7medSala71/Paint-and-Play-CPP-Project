#pragma once
#include"operation.h"
#include"../Shapes/RegPol.h"
class opAddRegPol:public operation
{
private:
    RegPol* pRPol;
public:
    opAddRegPol(controller* pCont);
    virtual ~opAddRegPol();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

