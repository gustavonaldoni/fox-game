#include "raylib.h"
#include "deathScreen.h"

void DrawCenteredText(const char *text, int y, int fontSize, Color color)
{
    int xText, yText;

    xText = (GetScreenWidth() - MeasureText(text, fontSize)) / 2;
    yText = y;

    DrawText(text, xText, yText, fontSize, color);
}

void DrawDeathScreenText()
{
    const char *deathText, *retryText;
    int yDeathText, yRetryText;
    int fontSizeDeath, fontSizeRetry;

    deathText = TextFormat("You died ...");
    retryText = TextFormat("Press 'SPACE' to try again");

    fontSizeDeath = 60;
    fontSizeRetry = (int)((float)fontSizeDeath / 1.5f);

    yDeathText = (GetScreenHeight() - MeasureTextEx(GetFontDefault(), deathText, fontSizeDeath, 1.0f).y) / 2;
    yRetryText = yDeathText + 70;

    DrawCenteredText(deathText, yDeathText, fontSizeDeath, RAYWHITE);
    DrawCenteredText(retryText, yRetryText, fontSizeRetry, RAYWHITE);
}