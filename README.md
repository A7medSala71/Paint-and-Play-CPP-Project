# Drawing Application

## Overview
This project is a **2D Drawing Application** built in **C++** using the **CMU Graphics Library**.  
It allows users to draw various shapes, manipulate them, and save or load drawings from custom text files.

The application is structured using **Object-Oriented Programming (OOP)** and follows a modular design with clear separation between GUI, Controller, Shapes, and Operations.

---

## Features
### Shape Drawing
- Rectangle
- Triangle
- Line
- Square
- Circle
- Oval
- Polygon
- Regular Polygon

### Shape Manipulation
- Select single shape
- Multi-selection (select multiple shapes)
- Resize by drag
- Rotate shapes
- Move shapes
- Send shape to back
- Delete single or multiple shapes

### Color & Style
- Change border color
- Change fill color
- Toggle fill ON/OFF
- Change border width

### File Management
- **Save** the current drawing to a text file
- **Load** a previously saved drawing
- **Custom text-based file format**:
  ```
  DrawColor FillColor BorderWidth
  ShapeCount
  SHAPE_TYPE ID shape-specific parameters drawColor fillColor/NO_FILL borderWidth
  ...
  ```

### Additional Features
- Attach an image inside a shape (optional)
- Zoom In/Out

---

## Example Save File
```
160 82 45	245 245 220	3
3
CIRCLE 1 509 314 100 0 100 0 NO_FILL 3
TRIANGLE 2 691 154 753 209 676 226 160 82 45 NO_FILL 3
OVAL 3 921 345 70 100 160 82 45 245 245 220 3

```

---

## Project Structure
```
DrawingApp/
│
├── main.cpp
├── controller.cpp
├── controller.h
├── Defs.h
│
├── GUI/
│   ├── GUI.cpp
│   ├── GUI.h
│   ├── CMUgraphicsLib/ (third-party library)
│
├── Shapes/
│   ├── Shape.h
│   ├── Shape.cpp
│   ├── Circle.h / Circle.cpp
│   ├── Rect.h / Rect.cpp
│   ├── Tri.h / Tri.cpp
│   ├── Line.h / Line.cpp
│   ├── Square.h / Square.cpp
│   ├── Oval.h / Oval.cpp
│   ├── RegPol.h / RegPol.cpp
│   ├── Pol.h / Pol.cpp
│
├── operations/
│   ├── operation.h
│   ├── opSelect.h / opSelect.cpp
│   ├── opMultiSelect.h / opMultiSelect.cpp
│   ├── opResizeDrag.h / opResizeDrag.cpp
│   ├── opRotate.h / opRotate.cpp
│   ├── opSave.h / opSave.cpp
│   ├── opLoad.h / opLoad.cpp
│   ├── opSendToBack.h / opSendToBack.cpp
│   ├── ...
│
├── Graph.cpp
├── Graph.h
│
└── README.md
```

---

## Installation & Setup

### Prerequisites
- **C++17 or later**
- **Visual Studio** (recommended) or any IDE supporting Windows API
- **CMU Graphics Library** (already included in `GUI/CMUgraphicsLib`)

### Steps
1. Clone or download this repository:
   ```bash
   git clone <repository_url>
   ```
2. Open the project in Visual Studio.
3. Make sure the CMU Graphics Library (`CMUgraphicsLib`) is properly referenced.
4. Build and run the project.

---

## Usage Instructions
1. Run the application.
2. Use the **toolbar icons** to:
   - Draw shapes
   - Select and modify shapes
   - Change colors and styles
3. Use the **side menu** for:
   - Rotate, resize, move, send to back
   - Multi-select and delete
4. Use **Save** to store your drawing and **Load** to open saved drawings.
5. Exit from the toolbar when done.

---

## Known Issues
- Single select initially malfunctioned after implementing save/load but fixed in later commits.
- Resize by drag is functional but not very smooth for rapid mouse movements.

---

## Future Enhancements
- Add group/ungroup functionality.
- Copy-Paste for shapes.
- Full Undo/Redo support.
- Export drawing as image (PNG/JPG).
- Better real-time resize visualization.

---

## Authors
- **Your Name**
- Email: *A7med.alah1416@gmail.com*

---

## License
This project is for **educational purposes**
