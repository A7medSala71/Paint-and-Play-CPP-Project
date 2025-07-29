#pragma once
#include"operations/operation.h"
class opZoomOut:public operation
{
    double factor;
    double reverseFactor;
    Point ref;
public:
    opZoomOut(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

