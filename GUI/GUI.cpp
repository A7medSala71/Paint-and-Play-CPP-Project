#include "GUI.h"

GUI::GUI()
{

	width = 1700;
	height = 800;
	wx = 5;
	wy = 5;


	StatusBarHeight = 50;
	ToolBarHeight = 50;
	MenuIconWidth = 70;

	DrawColor = DARKGREEN;	//default Drawing color
	FillColor = WHITE;	//default Filling color
	MsgColor = BLUE;		//Messages color
	BkGrndColor = WHITE;	//Background color
	HighlightColor = MAGENTA;	//This color should NOT be used to draw shapes. use it for highlight only
	StatusBarColor = LIGHTSEAGREEN;
	PenWidth = 3;	//default width of the shapes frames
	IsFilled = false;


	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - PAINT ^ ^ PLAY - - - - - - - - - -");

	CreateDrawToolBar();
	CreateStatusBar();
}




//======================================================================================//
//								Input Functions										//
//======================================================================================//
void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if( Label.size() > 0)	
				Label.resize(Label.size() - 1);
			else
				Key = '\0';		
		else
			Label += Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);

	// ---------- Horizontal Toolbar ----------
	if (y >= 0 && y < ToolBarHeight) {
		int ClickedIconOrder = (x / MenuIconWidth);
		switch (ClickedIconOrder)
		{
		case ICON_RECT: return DRAW_RECT;
		case ICON_TRI: return DRAW_TRI;
		case ICON_Line: return DRAW_LINE;
		case ICON_Sqr: return DRAW_Sqr;
		case ICON_Circ: return DRAW_CIRC;
		case ICON_Oval: return Draw_Oval;
		case ICON_RegPol: return Draw_RegPol;
		case ICON_Pol: return Draw_Pol;
		case ICON_Undo: return UNDO;
		case ICON_Redo: return REDO;
		case ICON_Select: return Select_Shape;
		case ICON_ChngPenCol: return CHNG_DRAW_CLR;
		case ICON_ChngFillCol: return CHNG_FILL_CLR;
		case ICON_StickIMG: return STICK_IMG;
		case ICON_ColorPalet: return Palette;
		case ICON_ZoomIn: return ZoomIn;
		case ICON_ZoomOut: return ZoomOut;
		case ICON_MultiSel: return MultiSel;
		case ICON_Save: return SAVE;
		case ICON_Load: return LOAD;
		case ICON_EXIT: return EXIT;


		default: return EMPTY;
		}
	}

	// ---------- Vertical Toolbar ----------
	if (x >= 0 && x < MenuIconWidth &&
		y >= ToolBarHeight && y < ToolBarHeight + DRAW_ICON_COUNTVert * MenuIconWidth)
	{
		int ClickedIconOrder = (y - ToolBarHeight) / MenuIconWidth;
		switch (ClickedIconOrder)
		{
		case ICON_ChngBorderCol: return ChngBorder;   
		case ICON_ChngFill: return ChngFill;   
		case ICON_Del: return DEL;   
		case Icon_Resize: return RESIZE; 
		case Icon_Rotate: return ROTATE;
		case Icon_Copy: return COPY;
		case Icon_Paste: return Paste;
		case Icon_Cut: return CUT;
		case Icon_Multidel: return MultiDel;
		case Icon_SendToBack: return SEND_BACK;

		default: return EMPTY;
		}
	}

	// ---------- Drawing Area ----------
	if (y >= ToolBarHeight && y < height - StatusBarHeight && x >= MenuIconWidth)
		return DRAWING_AREA;

	// ---------- Status Bar ----------
	return STATUS;
}
////////////////////////////////////////////////////



//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar()
{
	// ---------- Horizontal Toolbar ----------
	string MenuIconImagesHz[DRAW_ICON_COUNTHz];
	MenuIconImagesHz[ICON_RECT] = "images\\MenuIcons\\Menu_Rect.jpg";
	MenuIconImagesHz[ICON_TRI] = "images\\MenuIcons\\Menu_Tri.jpg";
	MenuIconImagesHz[ICON_Line] = "images\\MenuIcons\\Menu_Line.jpeg";
	MenuIconImagesHz[ICON_Sqr] = "images\\MenuIcons\\Menu_Sqr.jpeg";
	MenuIconImagesHz[ICON_Circ] = "images\\MenuIcons\\Menu_Circ.jpeg";
	MenuIconImagesHz[ICON_Oval] = "images\\MenuIcons\\Menu_Oval.jpeg";
	MenuIconImagesHz[ICON_RegPol] = "images\\MenuIcons\\Menu_RegPol.jpeg";
	MenuIconImagesHz[ICON_Pol] = "images\\MenuIcons\\Menu_Pol.jpeg";
	MenuIconImagesHz[ICON_Undo] = "images\\MenuIcons\\Menu_Undo.jpeg";
	MenuIconImagesHz[ICON_Redo] = "images\\MenuIcons\\Menu_Redo.jpeg";
	MenuIconImagesHz[ICON_Select] = "images\\MenuIcons\\Menu_Select.jpeg";
	MenuIconImagesHz[ICON_ChngPenCol] = "images\\MenuIcons\\Menu_ChgPenCol.jpeg";
	MenuIconImagesHz[ICON_ChngFillCol] = "images\\MenuIcons\\Menu_Fill.jpeg";
	MenuIconImagesHz[ICON_StickIMG] = "images\\MenuIcons\\Menu_StickIMG.jpeg";
	MenuIconImagesHz[ICON_ColorPalet] = "images\\MenuIcons\\Menu_ColPalet.jpeg";
	MenuIconImagesHz[ICON_ZoomIn] = "images\\MenuIcons\\Menu_ZoomIn.jpeg";
	MenuIconImagesHz[ICON_ZoomOut] = "images\\MenuIcons\\Menu_ZoomOut.jpeg";
	MenuIconImagesHz[ICON_MultiSel] = "images\\MenuIcons\\Menu_MultiSel.jpeg";
	MenuIconImagesHz[ICON_Save] = "images\\MenuIcons\\Menu_Save.jpeg";
	MenuIconImagesHz[ICON_Load] = "images\\MenuIcons\\Menu_Load.jpeg";

	MenuIconImagesHz[ICON_EXIT] = "images\\MenuIcons\\Menu_Exit.jpg";

	for (int i = 0; i < DRAW_ICON_COUNTHz; i++)
		pWind->DrawImage(MenuIconImagesHz[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);
}
void GUI::CreateVerticalToolBar()
{
	// ---------- Vertical Toolbar ----------
	string MenuIconImagesVer[DRAW_ICON_COUNTVert];
	MenuIconImagesVer[ICON_ChngBorderCol] = "images\\MenuIcons\\Menu_ChngBorder.jpeg";
	MenuIconImagesVer[ICON_ChngFill] = "images\\MenuIcons\\Menu_ChngFill.jpeg";
	MenuIconImagesVer[ICON_Del] = "images\\MenuIcons\\Menu_Delete.jpeg";
	MenuIconImagesVer[Icon_Resize] = "images\\MenuIcons\\Menu_Resize.jpeg";
	MenuIconImagesVer[Icon_Rotate] = "images\\MenuIcons\\Menu_Rotate.jpeg";
	MenuIconImagesVer[Icon_Copy] = "images\\MenuIcons\\Menu_Copy.jpeg";
	MenuIconImagesVer[Icon_Paste] = "images\\MenuIcons\\Menu_Paste.jpeg";
	MenuIconImagesVer[Icon_Cut] = "images\\MenuIcons\\Menu_Cut.jpeg";
	MenuIconImagesVer[Icon_Multidel] = "images\\MenuIcons\\Menu_MultiDel.jpeg";
	MenuIconImagesVer[Icon_SendToBack] = "images\\MenuIcons\\Menu_SendToBack.jpeg";

	for (int i = 0; i < DRAW_ICON_COUNTVert; i++)
		pWind->DrawImage(MenuIconImagesVer[i], 0, ToolBarHeight + i * MenuIconWidth, MenuIconWidth, MenuIconWidth);

	pWind->SetPen(RED, 3);
	pWind->DrawLine(MenuIconWidth, ToolBarHeight, MenuIconWidth, height - StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////



void GUI::ClearDrawArea() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);

}
window* GUI::GetWindow() const
{
	return pWind;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.75 * StatusBarHeight), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{
	return DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{
	return FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{
	return PenWidth;
}

void GUI::SetCrntDrawColor(color c)
{
	DrawColor = c;
}

void GUI::SetCrntFillColor(color c)
{
	FillColor = c;
}

void GUI::SetCrntPenWidth(int w)
{
	PenWidth = w;
}

color GUI::getBGColor() const
{
	return BkGrndColor;
}

bool GUI::getIsFilled() const
{
	return IsFilled;
}

void GUI::enableFilling()
{
	IsFilled = true;
}

void GUI::disableFilling()
{
	IsFilled = false;
}

void GUI::setIsFilled(bool filled)
{
	IsFilled = filled;
}


//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const
{
	color DrawingClr;
	if (RectGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
}

void GUI::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo) const
{
	color DrawingClr;
	if (LineGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y);

}

void GUI::DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo) const
{
	color DrawingClr;
	if (TriGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);

}

void GUI::DrawSquare(Point center, int length, GfxInfo SquareGfxInfo) const
{
	color DrawingClr;
	if (SquareGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = SquareGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, SquareGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (SquareGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillClr);
	}
	else
		style = FRAME;
	Point P1 = { center.x - length / 2, center.y - length / 2 };
	Point P2 = { center.x + length / 2, center.y + length / 2 };

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);


}
void GUI::DrawCircle(Point center, int radius, GfxInfo CircleInfo) const
{
	color DrawingClr;
	if (CircleInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = CircleInfo.DrawClr;

	pWind->SetPen(DrawingClr, CircleInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (CircleInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawCircle(center.x,center.y,radius, style);

}
void GUI::DrawOval(Point center, int Horizontal_diam, int Vert_diam, GfxInfo OvalInfo) const
{
	color DrawingClr;
	if (OvalInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = OvalInfo.DrawClr;

	pWind->SetPen(DrawingClr, OvalInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (OvalInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(OvalInfo.FillClr);
	}
	else
		style = FRAME;
	Point P1 = { center.x - Horizontal_diam / 2, center.y - Vert_diam / 2 };
	Point P2 = { center.x + Horizontal_diam / 2, center.y + Vert_diam / 2 };

	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);
	

}
void GUI::DrawPol(int numofvert, int* arr_x, int*arr_y, GfxInfo PolInfo) const
{
	color DrawingClr;
	if (PolInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = PolInfo.DrawClr;

	pWind->SetPen(DrawingClr, PolInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (PolInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(PolInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawPolygon(arr_x,arr_y,numofvert,style);

}
void GUI::DrawRegPol(int numofvert, int* arr_x, int* arr_y, GfxInfo RegPolInfo) const
{
	color DrawingClr;
	if (RegPolInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = RegPolInfo.DrawClr;

	pWind->SetPen(DrawingClr, RegPolInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RegPolInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RegPolInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawPolygon(arr_x, arr_y, numofvert, style);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

