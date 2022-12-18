#include <stdbool.h>
#include "raylib.h"
#include "raymath.h"
#include "volumeBar.h"

void CreateVolumeBar(VolumeBar *volumeBar, int x, int y, int width, int height)
{
    Rectangle lineRectangle = {0}, filledRectangle = {0};

    volumeBar->x = x;
    volumeBar->y = y;
    volumeBar->width = width;
    volumeBar->height = height;

    volumeBar->color = RAYWHITE;

    lineRectangle = (Rectangle){volumeBar->x, volumeBar->y, volumeBar->width, volumeBar->height};
    filledRectangle = (Rectangle){volumeBar->x, volumeBar->y, 0, volumeBar->height};

    volumeBar->lineRectangle = lineRectangle;
    volumeBar->filledRectangle = filledRectangle;
}

bool UserHasClickedOnVolumeBar(VolumeBar volumeBar)
{
    return CheckCollisionPointRec(GetMousePosition(), volumeBar.lineRectangle) &&
           IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}

void UpdateVolumeBar(VolumeBar *volumeBar, float *volume)
{
    int newFilledWidth = 0;

    if (UserHasClickedOnVolumeBar(*volumeBar))
    {
        newFilledWidth = GetMouseX() - volumeBar->lineRectangle.x;
        volumeBar->filledRectangle.width = newFilledWidth;

        *volume = Remap(newFilledWidth, 0.0f, volumeBar->lineRectangle.width, MIN_VOLUME, MAX_VOLUME);
    }
}

void DrawVolumeBar(VolumeBar volumeBar)
{
    DrawRectangleLines(volumeBar.lineRectangle.x, volumeBar.lineRectangle.y, volumeBar.lineRectangle.width, volumeBar.lineRectangle.height, volumeBar.color);
    DrawRectangleRec(volumeBar.filledRectangle, volumeBar.color);
}