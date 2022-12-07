#include "raylib.h"
#include "stopwatch.h"
#include "background.h"

void CreateBackground(Background *background, Texture2D texture)
{
    background->texture = texture;
    background->xMovement = 0;
    background->yMovement = 0;
    background->movementStopwatch = StopwatchCreate(0.02f);
    background->tint = RAYWHITE;
}

void ShowBackground(Background background)
{
    const float rotation = 0.0f, scaleFactor = 5.1f;
    Rectangle source, destination;
    Vector2 origin;

    source = (Rectangle){background.xMovement,
                         background.yMovement,
                         background.texture.width,
                         background.texture.height};

    destination = (Rectangle){0,
                              0,
                              background.texture.width * scaleFactor,
                              background.texture.height * scaleFactor};

    origin = (Vector2){0, 0};

    DrawTexturePro(background.texture, source, destination, origin, rotation, background.tint);
}

void MoveBackground(Background *background)
{
    StopwatchUpdate(&background->movementStopwatch);

    if (StopwatchIsDone(background->movementStopwatch))
    {
        StopwatchReset(&background->movementStopwatch);
        background->xMovement += 1;

        if (background->xMovement >= background->texture.width)
            background->xMovement = 0;
    }
}