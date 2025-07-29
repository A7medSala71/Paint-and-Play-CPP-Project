#pragma once
#include "Shape.h"
#include <fstream>
#include<iostream>
#include<vector>
#include"Line.h"
#include"Circle.h"
#include"Oval.h"
#include"pol.h"
#include"Rect.h"
#include"RegPol.h"
#include"../Square.h"
#include"Tri.h"
using namespace std;

//forward decl
class GUI;	

//A class that is responsible on everything related to shapes
class Graph
{
	enum { maxShapeCount = 1000 };
private:
	shape* shapesList[maxShapeCount]; //a container to hold all shapes							   
	int shapeCount;			// Actual number of shapes stored in the list
	shape* selectedShape;	//pointer to the currently selected shape
	vector<shape*> selectedShapes;
	int nextID;   
public:										
	Graph();
	~Graph();
	void Addshape(shape* pFig); //Adds a new shape to the shapesList
	void Draw(GUI* pUI) const;			//Draw the graph (draw all shapes)
	shape* Getshape(int x, int y) const; //Search for a shape given a point inside the shape

	void SaveShapes(ofstream& outfile, GUI* pUI);	//Save all shapes to a file
	void LoadShapes(ifstream& infile, GUI* pUI);	//Save all shapes to a file
	void RemoveShape(shape* s);
	void UnselectAll();
	void SetSelectedShape(shape* pShape);
	shape* GetSelectedShape() const;
	int GetShapeIndex(shape* s) const;
	void InsertShapeAt(shape* s, int index);
	void Zoom(double factor, Point ref);
	void AddToSelection(shape* s);
	void RemoveFromSelection(shape* s);
	void ClearSelection();
	bool IsShapeSelected(shape* s) const;
	vector<shape*> GetSelectedShapes()const;
	void SendToBack(shape* s);
};
