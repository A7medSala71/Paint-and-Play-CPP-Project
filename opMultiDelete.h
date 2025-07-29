#pragma once
#include "operations/operation.h"
#include <vector>
#include"Shapes/Shape.h"
class opMultiDelete : public operation
{
    std::vector<shape*> deletedShapes;
public:
    opMultiDelete(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};