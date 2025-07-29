#pragma once
#include "../operations/operation.h"
#include "../Shapes/Shape.h"

class opRotate : public operation {
    shape* SelectedShape;
public:
    opRotate(controller* pCont);
    virtual ~opRotate() {}
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};
