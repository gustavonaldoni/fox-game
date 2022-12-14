#include "raylib.h"
#include "player.h"
#include "score.h"

void UpdateScore(Player *player, int scoreToAdd)
{
    player->score += scoreToAdd;
}

void DrawScore(int score)
{
    int borderSpace, shadowSpace;
    int xText, yText;
    int textWidth;
    const char *text;
    int fontSize;

    borderSpace = 10;
    shadowSpace = 3;
    fontSize = 40;

    text = TextFormat("%d", score);
    textWidth = MeasureTextEx(GetFontDefault(), text, fontSize, 5.0f).x;

    yText = borderSpace;
    xText = GetScreenWidth() - borderSpace - textWidth;

    DrawText(text, xText + shadowSpace, yText + shadowSpace, fontSize, DARKGRAY);
    DrawText(text, xText, yText, fontSize, RAYWHITE);
}