#pragma once
#include "operations/operation.h"
class opChangePenColor:public operation
{
private:
	color OldColor, NewColor;
public:
    opChangePenColor(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();

};

