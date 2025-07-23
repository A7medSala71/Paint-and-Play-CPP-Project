#include "ColorPalette.h"
ColorPalette::ColorPalette()
{
}

color ColorPalette::PickColor()
{
    // Calculate grid size
    const int cols = 12;  // 12 columns
    const int rows = 11;  // 11 rows -> 132 cells (enough for 120+ colors)
    const int block = 40;

    window* pPalette = new window(cols * block, rows * block, 200, 100);
    pPalette->ChangeTitle("Color Palette");

    // Full color table (manually listed based on colors.h)
    color paletteColors[11][12] = {
        {SNOW, GHOSTWHITE, WHITESMOKE, GAINSBORO, FLORALWHITE, OLDLACE, LINEN, ANTIQUEWHITE, PAPAYAWHIP, BLANCHEDALMOND, BISQUE, PEACHPUFF},
        {NAVAJOWHITE, MOCCASIN, CORNSILK, IVORY, LEMONCHIFFON, SEASHELL, HONEYDEW, MINTCREAM, AZURE, ALICEBLUE, LAVENDER, LAVENDERBLUSH},
        {MISTYROSE, WHITE, BLACK, DARKSLATEGRAY, DIMGRAY, SLATEGRAY, LIGHTSLATEGRAY, GRAY, LIGHTGREY, MIDNIGHTBLUE, NAVY, CORNFLOWERBLUE},
        {DARKSLATEBLUE, SLATEBLUE, MEDIUMSLATEBLUE, LIGHTSLATEBLUE, MEDIUMBLUE, ROYALBLUE, BLUE, DODGERBLUE, DEEPSKYBLUE, SKYBLUE, LIGHTSKYBLUE, STEELBLUE},
        {LIGHTSTEELBLUE, LIGHTBLUE, POWDERBLUE, PALETURQUOISE, DARKTURQUOISE, MEDIUMTURQUOISE, TURQUOISE, CYAN, LIGHTCYAN, CADETBLUE, MEDIUMAQUAMARINE, AQUAMARINE},
        {DARKGREEN, DARKOLIVEGREEN, DARKSEAGREEN, SEAGREEN, MEDIUMSEAGREEN, LIGHTSEAGREEN, PALEGREEN, SPRINGGREEN, LAWNGREEN, GREEN, CHARTREUSE, MEDIUMSPRINGGREEN},
        {GREENYELLOW, LIMEGREEN, YELLOWGREEN, FORESTGREEN, OLIVEDRAB, DARKKHAKI, KHAKI, PALEGOLDENROD, LIGHTGOLDENRODYELLOW, LIGHTYELLOW, YELLOW, GOLD},
        {LIGHTGOLDENROD, GOLDENROD, DARKGOLDENROD, ROSYBROWN, INDIANRED, SADDLEBROWN, SIENNA, PERU, BURLYWOOD, BEIGE, WHEAT, SANDYBROWN},
        {TAN, CHOCOLATE, FIREBRICK, BROWN, DARKSALMON, SALMON, LIGHTSALMON, ORANGE, DARKORANGE, CORAL, LIGHTCORAL, TOMATO},
        {ORANGERED, RED, HOTPINK, DEEPPINK, PINK, LIGHTPINK, PALEVIOLETRED, MAROON, MEDIUMVIOLETRED, VIOLETRED, MAGENTA, VIOLET},
        {PLUM, ORCHID, MEDIUMORCHID, DARKORCHID, DARKVIOLET, BLUEVIOLET, PURPLE, MEDIUMPURPLE, THISTLE, DARKGREY, DARKGRAY, LIGHTGREEN}
    };

    // Draw color cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pPalette->SetBrush(paletteColors[i][j]);
            pPalette->SetPen(paletteColors[i][j], 1);
            pPalette->DrawRectangle(j * block, i * block,
                (j + 1) * block, (i + 1) * block);
        }
    }

    // Wait for user click
    int x, y;
    pPalette->WaitMouseClick(x, y);
    int row = y / block;
    int col = x / block;

    color selectedColor = paletteColors[row][col];
    delete pPalette; // Close palette window
    return selectedColor;
}
