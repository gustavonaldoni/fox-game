#include "raylib.h"
#include "numberOfRounds.h"

void DrawRoundNumber(int roundNumber)
{
    const int shadowSpace = 5, borderSpace = 20;
    const char *text;
    int x, y;
    int textWidth, textHeight, fontSize;

    fontSize = 50;
    text = TextFormat("Round %d", roundNumber);

    textWidth = MeasureTextEx(GetFontDefault(), text, fontSize, 5.0f).x;
    textHeight = MeasureTextEx(GetFontDefault(), text, fontSize, 5.0f).y;

    x = GetScreenWidth() - textWidth - borderSpace;
    y = GetScreenHeight() - textHeight - borderSpace;

    DrawTextEx(GetFontDefault(), text, (Vector2){x + shadowSpace, y + shadowSpace}, fontSize, 5.0f, DARKGRAY);
    DrawTextEx(GetFontDefault(), text, (Vector2){x, y}, fontSize, 5.0f, RAYWHITE);
}