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
#include<fstream>
Graph::Graph()
{
	shapeCount = 0;
	selectedShape = nullptr;
	nextID = 1;
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
	if (shapeCount < maxShapeCount) {
		pShp->setID(nextID++);   // <--- Assign unique ID automatically
		shapesList[shapeCount++] = pShp;

	}
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


void Graph::SaveShapes(std::ofstream& outFile, GUI* pGUI)
{
	// Save current draw color, fill color, pen width
	color draw = pGUI->getCrntDrawColor();
	color fill = pGUI->getCrntFillColor();
	int penWidth = pGUI->getCrntPenWidth();

	outFile << (int)draw.ucRed << " "
		<< (int)draw.ucGreen << " "
		<< (int)draw.ucBlue << "\t"
		<< (int)fill.ucRed << " "
		<< (int)fill.ucGreen << " "
		<< (int)fill.ucBlue << "\t"
		<< penWidth << "\n";

	// Save number of shapes
	outFile << shapeCount << "\n";

	// Save all shapes
	for (int i = 0; i < shapeCount; i++)
		shapesList[i]->Save(outFile);
}

void Graph::LoadShapes(ifstream& inFile, GUI* pUI)
{
	// Clear existing shapes
	shapeCount = 0;
	selectedShape = nullptr;
	selectedShapes.clear();

	int drawR, drawG, drawB;
	int fillR, fillG, fillB;
	int penWidth;

	// Read default drawing colors & pen width
	inFile >> drawR >> drawG >> drawB >> fillR >> fillG >> fillB >> penWidth;
	color defaultDraw = { (unsigned char)drawR, (unsigned char)drawG, (unsigned char)drawB };
	color defaultFill = { (unsigned char)fillR, (unsigned char)fillG, (unsigned char)fillB };

	// Read number of shapes
	int numShapes;
	inFile >> numShapes;

	for (int i = 0; i < numShapes; i++)
	{
		string type;
		int id;
		inFile >> type >> id;

		// -------------------- RECT --------------------
		if (type == "RECT") {
			int x1, y1, x2, y2, r, g, b, penW;
			string fillToken;
			inFile >> x1 >> y1 >> x2 >> y2 >> r >> g >> b >> fillToken >> penW;

			GfxInfo gfx;
			gfx.DrawClr = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
			gfx.BorderWdth = penW;
			gfx.isFilled = false;

			if (fillToken != "NO_FILL") {
				int fr = stoi(fillToken);
				int fg, fb;
				inFile >> fg >> fb;
				gfx.isFilled = true;
				gfx.FillClr = { (unsigned char)fr, (unsigned char)fg, (unsigned char)fb };
			}

			Rect* rect = new Rect({ x1, y1 }, { x2, y2 }, gfx);
			rect->setID(id);
			Addshape(rect);
		}

		// -------------------- CIRCLE --------------------
		else if (type == "CIRCLE") {
			int cx, cy, radius, r, g, b, penW;
			string fillToken;
			inFile >> cx >> cy >> radius >> r >> g >> b >> fillToken >> penW;

			GfxInfo gfx;
			gfx.DrawClr = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
			gfx.BorderWdth = penW;
			gfx.isFilled = false;

			if (fillToken != "NO_FILL") {
				int fr = stoi(fillToken);
				int fg, fb;
				inFile >> fg >> fb;
				gfx.isFilled = true;
				gfx.FillClr = { (unsigned char)fr, (unsigned char)fg, (unsigned char)fb };
			}

			Circle* circle = new Circle({ cx, cy }, radius, gfx);
			circle->setID(id);
			Addshape(circle);
		}

		// -------------------- TRIANGLE --------------------
		else if (type == "TRIANGLE") {
			int x1, y1, x2, y2, x3, y3, r, g, b, penW;
			string fillToken;
			inFile >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> r >> g >> b >> fillToken >> penW;

			GfxInfo gfx;
			gfx.DrawClr = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
			gfx.BorderWdth = penW;
			gfx.isFilled = false;

			if (fillToken != "NO_FILL") {
				int fr = stoi(fillToken);
				int fg, fb;
				inFile >> fg >> fb;
				gfx.isFilled = true;
				gfx.FillClr = { (unsigned char)fr, (unsigned char)fg, (unsigned char)fb };
			}

			Tri* tri = new Tri({ x1, y1 }, { x2, y2 }, { x3, y3 }, gfx);
			tri->setID(id);
			Addshape(tri);
		}

		// -------------------- LINE --------------------
		else if (type == "LINE") {
			int x1, y1, x2, y2, r, g, b, penW;
			inFile >> x1 >> y1 >> x2 >> y2 >> r >> g >> b >> penW;

			GfxInfo gfx;
			gfx.DrawClr = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
			gfx.BorderWdth = penW;
			gfx.isFilled = false;

			Line* line = new Line({ x1, y1 }, { x2, y2 }, gfx);
			line->setID(id);
			Addshape(line);
		}

		// -------------------- SQUARE --------------------
		else if (type == "SQUARE") {
			int cx, cy, sideLength, r, g, b, penW;
			string fillToken;
			inFile >> cx >> cy >> sideLength >> r >> g >> b >> fillToken >> penW;

			GfxInfo gfx;
			gfx.DrawClr = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
			gfx.BorderWdth = penW;
			gfx.isFilled = false;

			if (fillToken != "NO_FILL") {
				int fr = stoi(fillToken);
				int fg, fb;
				inFile >> fg >> fb;
				gfx.isFilled = true;
				gfx.FillClr = { (unsigned char)fr, (unsigned char)fg, (unsigned char)fb };
			}

			Square* sq = new Square({ cx, cy }, sideLength, gfx);
			sq->setID(id);
			Addshape(sq);
		}

		// -------------------- REGPOL --------------------
		else if (type == "REGPOL") {
			int cx, cy, numVertices, r, g, b, penW;
			double radius;
			string fillToken;
			inFile >> cx >> cy >> radius >> numVertices >> r >> g >> b >> fillToken >> penW;

			GfxInfo gfx;
			gfx.DrawClr = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
			gfx.BorderWdth = penW;
			gfx.isFilled = false;

			if (fillToken != "NO_FILL") {
				int fr = stoi(fillToken);
				int fg, fb;
				inFile >> fg >> fb;
				gfx.isFilled = true;
				gfx.FillClr = { (unsigned char)fr, (unsigned char)fg, (unsigned char)fb };
			}

			// pick a point on the circle to compute radius & orientation
			Point radPT = { (int)(cx + radius), cy };

			RegPol* rp = new RegPol({ cx, cy }, radPT, numVertices, gfx);
			rp->setID(id);
			Addshape(rp);
			}

		// -------------------- POLY --------------------
		else if (type == "POLY") {
			int vertexCount, r, g, b, penW;
			inFile >> vertexCount;

			int* x = new int[vertexCount];
			int* y = new int[vertexCount];
			for (int j = 0; j < vertexCount; j++)
				inFile >> x[j] >> y[j];

			string fillToken;
			inFile >> r >> g >> b >> fillToken >> penW;

			GfxInfo gfx;
			gfx.DrawClr = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
			gfx.BorderWdth = penW;
			gfx.isFilled = false;

			if (fillToken != "NO_FILL") {
				int fr = stoi(fillToken);
				int fg, fb;
				inFile >> fg >> fb;
				gfx.isFilled = true;
				gfx.FillClr = { (unsigned char)fr, (unsigned char)fg, (unsigned char)fb };
			}

			pol* polygon = new pol(vertexCount, x, y, gfx);
			polygon->setID(id);
			Addshape(polygon);

			delete[] x;
			delete[] y;
		}

		// -------------------- OVAL --------------------
		else if (type == "OVAL") {
			int cx, cy, horiz, vert, r, g, b, penW;
			string fillToken;
			inFile >> cx >> cy >> horiz >> vert >> r >> g >> b >> fillToken >> penW;

			GfxInfo gfx;
			gfx.DrawClr = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
			gfx.BorderWdth = penW;
			gfx.isFilled = false;

			if (fillToken != "NO_FILL") {
				int fr = stoi(fillToken);
				int fg, fb;
				inFile >> fg >> fb;
				gfx.isFilled = true;
				gfx.FillClr = { (unsigned char)fr, (unsigned char)fg, (unsigned char)fb };
			}

			Oval* oval = new Oval({ cx, cy }, horiz, vert, gfx);
			oval->setID(id);
			Addshape(oval);
		}
	}
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

int Graph::GetShapeIndex(shape* s) const
{
	for (int i = 0; i < shapeCount; i++)
		if (shapesList[i] == s)
			return i;
	return -1;
}

void Graph::InsertShapeAt(shape* s, int index)
{
	if (shapeCount >= maxShapeCount) return;

	if (index < 0 || index > shapeCount)
		index = shapeCount;  // fallback to end

	for (int i = shapeCount; i > index; i--)
		shapesList[i] = shapesList[i - 1];

	shapesList[index] = s;
	shapeCount++;
}

void Graph::Zoom(double factor, Point ref)
{
	for (int i = 0; i < shapeCount; i++)
		shapesList[i]->Zoom(factor, ref);
}
void Graph::AddToSelection(shape* s)
{
	if (!s) return;
	if (!IsShapeSelected(s)) {
		selectedShapes.push_back(s);
		s->SetSelected(true);
	}
}

void Graph::RemoveFromSelection(shape* s)
{
	if (!s) return;
	auto it = std::find(selectedShapes.begin(), selectedShapes.end(), s);
	if (it != selectedShapes.end()) {
		(*it)->SetSelected(false);
		selectedShapes.erase(it);
	}
}

void Graph::ClearSelection()
{
	for (auto* s : selectedShapes)
		s->SetSelected(false);
	selectedShapes.clear();
}

bool Graph::IsShapeSelected(shape* s) const
{
	return std::find(selectedShapes.begin(), selectedShapes.end(), s) != selectedShapes.end();
}

vector<shape*> Graph::GetSelectedShapes() const
{
	return selectedShapes;
}
void Graph::SendToBack(shape* s)
{
	if (!s) return;

	int index = GetShapeIndex(s);
	if (index == -1 || index == 0) return; // Already at back or not found

	// Remove shape from current position
	for (int i = index; i > 0; --i)
	{
		shapesList[i] = shapesList[i - 1];
	}

	// Place shape at index 0
	shapesList[0] = s;
}
