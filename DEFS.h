#ifndef DEFS_H
#define DEFS_H


//This file contais some global constants and definitions to be used in the project.
enum operationType //The operations supported (you can add more if needed)
{
	DRAW_RECT,		//Draw Rectangle
	DRAW_TRI,		//Draw Triangle
	DRAW_LINE,		//Draw Line
	DRAW_Sqr,
	DRAW_CIRC,		//Draw Circle
	Draw_Oval,
	Draw_RegPol,
	Draw_Pol,
	UNDO,
	REDO,
	Select_Shape,
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_FILL_CLR,	//Change the filling color
	STICK_IMG,
	Palette,
	ChngBorder,
	ChngFill,
	DEL,			//Delete a shape(s)
	RESIZE,			//Resize a shape(s)
	ROTATE,			//Rotate a shape(s)
	COPY,
	Paste,
	CUT,
	ZoomIn,
	ZoomOut,
	MultiSel,
	MultiDel,
	SEND_BACK,		//Send a shape to the back of all shapes
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	EXIT,			//Exit the application
	CHNG_BK_CLR,	//Change background color
	MOVE,			//Move a shape(s)
	BRNG_FRNT,		//Bring a shape to the front of all shapes

	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar

	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY			//Switch interface to Play mode

	///TODO: Add more operation types (if needed)
};

#endif