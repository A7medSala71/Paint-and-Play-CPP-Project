#include "Graph.h"
#include"Shape.h"
#include"Rect.h"
#include "../GUI/GUI.h"
#include"Circle.h"
#include"Tri.h"
#include"../Square.h"
#include"Line.h"
#include"RegPol.h"
#include"Oval.h"
#include"pol.h"
Graph::Graph()
{
	shapeCount = 0;
	selectedShape = nullptr;
}

Graph::~Graph()
{
}

//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//

//Add a shape to the list of shapes
void Graph::Addshape(shape* pShp)
{
	//Add a new shape to the shapes list
	if(shapeCount<maxShapeCount)
		shapesList[shapeCount++] = pShp;
}
////////////////////////////////////////////////////////////////////////////////////
//Draw all shapes on the user interface
void Graph::Draw(GUI* pUI) const
{
	pUI->ClearDrawArea();
	for (int i=0;i<shapeCount; i++)
		shapesList[i]->Draw(pUI);
}


shape* Graph::Getshape(int x, int y) const
{
	Point p = { x, y };

	// Search from topmost shape to back
	for (int i = shapeCount - 1; i >= 0; --i)
	{
		Circle* circ = dynamic_cast<Circle*>(shapesList[i]);
		if (circ)
		{
			Point c = circ->getcenter();
			int rad = circ->getrad();
			int dx = x - c.x;
			int dy = y - c.y;
			if (dx * dx + dy * dy <= rad * rad)
				return circ;
		}
		Rect* rect = dynamic_cast<Rect*>(shapesList[i]);
		if (rect)
		{
			// Extract rectangle corners
			Point c1 = rect->getCorner1();
			Point c2 = rect->getCorner2();

			// Calculate bounding box
			int left = min(c1.x, c2.x);
			int right = max(c1.x, c2.x);
			int top = min(c1.y, c2.y);
			int bottom = max(c1.y, c2.y);

			// Check if (x,y) is within rectangle
			if (x >= left && x <= right && y >= top && y <= bottom)
				return rect;
		}
		Tri* tr = dynamic_cast<Tri*>(shapesList[i]);
		if (tr)
		{
			Point P = { x, y };
			Point c1 = tr->GetPoint1();
			Point c2 = tr->GetPoint2();
			Point c3 = tr->GetPoint3();

			// Distances between triangle corners
			double l1 = dist(c1, c2);
			double l2 = dist(c2, c3);
			double l3 = dist(c3, c1);

			// Original triangle area
			double theta = anglebet2sides(l1, l2, l3);
			double area = areausingcoslaw(l1, l2, theta);

			// Distances to point P
			double lP1 = dist(P, c1);
			double lP2 = dist(P, c2);
			double lP3 = dist(P, c3);

			// Area of triangle P,1,2
			double thetaP12 = anglebet2sides(lP1, lP2, l1);
			double areaP12 = areausingcoslaw(lP1, lP2, thetaP12);

			// Area of triangle P,2,3
			double thetaP23 = anglebet2sides(lP2, lP3, l2);
			double areaP23 = areausingcoslaw(lP2, lP3, thetaP23);

			// Area of triangle P,3,1
			double thetaP13 = anglebet2sides(lP1, lP3, l3);
			double areaP13 = areausingcoslaw(lP1, lP3, thetaP13);

			// Total sub-areas
			double AreaSum = areaP12 + areaP23 + areaP13;

			// Allow small floating-point error
			if (fabs(AreaSum - area) < 1e-2) {
				return tr;
			}
		}
		Square* sqr = dynamic_cast<Square*>(shapesList[i]);
		if (sqr)
		{
			Point p = { x,y };
			Point cen = sqr->GetCenter();
			int slen = sqr->GetSlength();
			Point corn = { cen.x + slen / 2,cen.y + slen/2 };
			// Check if (x,y) is within rectangle
			if (dist(cen,p)<=dist(cen,corn))
				return sqr;
		}
		Line* lin = dynamic_cast<Line*>(shapesList[i]);
		if (lin)
		{
			Point p = { x,y };
			Point StartP = lin->GetStartPoint();
			Point EndP = lin->GetEndPoint();

			double totalLen = dist(StartP, EndP);
			double len1 = dist(StartP, p);
			double len2 = dist(p, EndP);
			if (fabs(totalLen - (len1 + len2)) < 1e-2) {
				return lin;
			}
		}
		RegPol* RPol = dynamic_cast<RegPol*>(shapesList[i]);
		if (RPol)
		{
			Point p = { x,y };
			Point center = RPol->Getcenter();
			double rad= RPol->GetRad();
			double l = dist(p, center);
			if (l<=rad) {
				return RPol;
			}
		}
		Oval* oval = dynamic_cast<Oval*>(shapesList[i]);
		if (oval) {
			Point center = oval->GetCenter();
			int a = oval->GetHorDiam();  // horizontal diameter
			int b = oval->GetVertDiam();    // vertical diameter

			double dx = x - center.x;
			double dy = y - center.y;

			double normalizedX = dx / (a / 2.0);
			double normalizedY = dy / (b / 2.0);

			if ((normalizedX * normalizedX + normalizedY * normalizedY) <= 1.0) {
				return oval;
			}
		}
		pol* polygon = dynamic_cast<pol*>(shapesList[i]);
		if (polygon) {
			Point p = { x, y };
			vector<Point> vertices = polygon->GetVertices();
			if (isPointInPolygon(vertices, p)) {
				return polygon;
			}
		}


	}

	return nullptr;
}

void Graph::RemoveShape(shape* s)
{
	for (int i = 0; i < shapeCount; ++i)
	{
		if (shapesList[i] == s)
		{
			// Do NOT delete the shape — caller owns it
			for (int j = i; j < shapeCount - 1; ++j)
				shapesList[j] = shapesList[j + 1];

			shapeCount--;
			return;
		}
	}
}

void Graph::UnselectAll()
{
	for (int i = 0; i < shapeCount; ++i) {
		shapesList[i]->SetSelected(false);
	}
}

void Graph::SetSelectedShape(shape* pShape)
{
	if (selectedShape)
		selectedShape->SetSelected(false);  // Un-highlight old

	selectedShape = pShape;

	if (selectedShape)
		selectedShape->SetSelected(true);   // Highlight new
}

shape* Graph::GetSelectedShape() const
{
	return selectedShape;
}
