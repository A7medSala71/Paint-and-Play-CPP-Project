#pragma once
#include"operation.h"
#include"../Shapes/Shape.h"
class opSelect:public operation
{
private:
    shape* oldSelection;
    shape* newSelection;
public:
    opSelect(controller* pCont);
    virtual ~opSelect();
    virtual void Execute();
    virtual void Undo(); 
    virtual void Redo();  
};

