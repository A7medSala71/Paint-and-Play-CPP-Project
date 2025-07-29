#pragma once
#include "operations/operation.h"
#include <fstream>
using namespace std;

class opLoad : public operation
{
private:
    string fileName;
public:
    opLoad(controller* pCont);
    virtual void ReadOperationParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
