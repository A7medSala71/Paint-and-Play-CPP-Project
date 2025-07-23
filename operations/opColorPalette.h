#pragma once
#include "operation.h"
class opColorPalette : public operation {
private:
    color PrevColor;
    color NewColor;
    bool PrevFillMode;
    bool NewFillMode;
    bool IsFillChange;
public:
    opColorPalette(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

