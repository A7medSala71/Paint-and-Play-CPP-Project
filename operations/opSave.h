#pragma once
#include "operation.h"
#include"../Shapes/Graph.h"
#include <fstream>
using namespace std;

class opSave : public operation
{
private:
    GUI* pGUI;
    Graph* pGraph;
    std::string Name;
    std::ofstream outFile;

    void ReadOperationParameters();

public:
    opSave(controller* pCont);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};