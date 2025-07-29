#pragma once
#include "operations/operation.h"
#include "Shapes/Shape.h"
#include<string>
#include<string.h>
#include<iostream>
using namespace std;

class opStickImage : public operation
{
private:
    shape* SelectedShape;
    std::string PrevImagePath;
    std::string NewImagePath;

public:
    opStickImage(controller* pCont);
    virtual ~opStickImage();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};