#pragma once



#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

#include <string>
using namespace std;

struct Point	//To be used for shapes points
{
	int x, y;
};

struct GfxInfo	//Graphical info common for all shapes (you may add more members)
{
	color DrawClr;	//Draw color of the shape
	color FillClr;	//Fill color of the shape
	bool isFilled;	//shape Filled or not
	int BorderWdth;	//Width of shape borders
	bool isSelected;	//true if the shape is selected.
};




class GUI
{
	enum MenuIconHz //The icons of the menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_RECT,		//Recangle icon in menu
		ICON_TRI,		//Triangle icon in menu
		ICON_Line,
		ICON_Sqr,
		ICON_Circ,
		ICON_Oval,
		ICON_RegPol,
		ICON_Pol,
		ICON_Undo,
		ICON_Redo,
		ICON_Select,
		ICON_ChngPenCol,
		ICON_ChngFillCol,
		ICON_StickIMG,
		ICON_ColorPalet,
		ICON_ZoomIn,
		ICON_ZoomOut,
		ICON_MultiSel,
		ICON_Save,
		ICON_Load,

		//TODO: Add more icons names here

		ICON_EXIT,		//Exit icon

		DRAW_ICON_COUNTHz		//no. of menu icons ==> This should be the last line in this enum
	};
	enum MenuIconVer {
		ICON_ChngBorderCol,
		ICON_ChngFill,
		ICON_Del,
		Icon_Resize,
		Icon_Rotate,
		Icon_Copy,
		Icon_Paste,
		Icon_Cut,
		Icon_Multidel,
		Icon_SendToBack,
		DRAW_ICON_COUNTVert
	};




	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuIconWidth;		//Width of each icon in toolbar menu


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes
	bool IsFilled;
	/// Add more members if needed



	window* pWind;

public:

	GUI();

	// Input Functions  ---------------------------
	void GetPointClicked(int& x, int& y) const;//Get coordinate where user clicks
	string GetSrting() const;	 //Returns a string entered by the user
	operationType GetUseroperation() const; //Read the user click and map to an operation

	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreateVerticalToolBar();
	void CreateStatusBar() const;	//create the status bar

	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area

	window* GetWindow() const;

	// -- shapes Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const;  //Draw a rectangle
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo) const;  //Draw a Line
	void DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo) const;  //Draw a Trinagle
	void DrawSquare(Point center, int length, GfxInfo SquareGfxInfo) const;
	void DrawCircle(Point center, int radius, GfxInfo CircleInfo) const;
	void DrawOval(Point center, int Horizontal_diam,int Vert_diam, GfxInfo OvalInfo) const;
	void DrawPol(int numofvert, int* arr_x, int* arr_y, GfxInfo PolInfo) const;
	void DrawRegPol(int numofvert, int* arr_x, int* arr_y, GfxInfo PolInfo) const;






	///Make similar functions for drawing all other shapes.

	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	void SetCrntDrawColor(color c);
	void SetCrntFillColor(color c);
	void SetCrntPenWidth(int w);
	color getBGColor() const;

	bool getIsFilled() const;

	void enableFilling();

	void disableFilling();

	void setIsFilled(bool filled);


	~GUI();
};

