#pragma once
#include "operations/operation.h"
class opZoomIn : public operation
{
    double factor;
    double reverseFactor;
    Point ref;
public:
    opZoomIn(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};