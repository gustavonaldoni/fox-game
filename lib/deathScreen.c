#include <stdlib.h>
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
    const char *deathText = NULL, *retryText = NULL;
    int yDeathText = 0, yRetryText = 0;
    int fontSizeDeath = 0, fontSizeRetry = 0;
    int deathTextHeight = 0, retryTextHeight = 0;
    int totalHeight = 0;
    const float spacing = 0.0f;

    deathText = TextFormat("You died ...");
    retryText = TextFormat("Press 'SPACE' to try again");

    fontSizeDeath = 60;
    fontSizeRetry = (int)((float)fontSizeDeath / 1.5f);

    deathTextHeight = MeasureTextEx(GetFontDefault(), deathText, fontSizeDeath, spacing).y;
    retryTextHeight = MeasureTextEx(GetFontDefault(), retryText, fontSizeRetry, spacing).y;

    totalHeight = deathTextHeight + retryTextHeight;

    yDeathText = (GetScreenHeight() - totalHeight) / 2;
    yRetryText = yDeathText + 70;

    DrawCenteredText(deathText, yDeathText, fontSizeDeath, RAYWHITE);
    DrawCenteredText(retryText, yRetryText, fontSizeRetry, RAYWHITE);
}