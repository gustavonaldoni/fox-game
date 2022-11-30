#include "raylib.h"
#include "stopwatch.h"
#include "player.h"
#include "enemy.h"

void AnimatePlayerTexture(Player *player, Stopwatch *stopwatch, int maxFrames, int *frame, float scaleFactor, Texture2D image)
{
    player->texture = image;
    float frameWidth = player->texture.width / maxFrames;
    const float rotation = 0.0f;

    StopwatchUpdate(stopwatch);

    if (StopwatchIsDone(*stopwatch))
    {
        StopwatchReset(stopwatch);
        *frame += 1;
    }

    *frame = *frame % maxFrames;

    DrawTexturePro(player->texture,
                   (Rectangle){frameWidth * (*frame), 0, frameWidth, player->texture.height},
                   (Rectangle){player->x, player->y, frameWidth * scaleFactor, player->texture.height * scaleFactor},
                   (Vector2){0, 0},
                   rotation,
                   RAYWHITE);
}

void AnimateEnemyTexture(Enemy *enemy, Stopwatch *stopwatch, int maxFrames, int *frame, float scaleFactor, Texture2D image)
{
    enemy->texture = image;
    float frameWidth = enemy->texture.width / maxFrames;
    const float rotation = 0.0f;

    StopwatchUpdate(stopwatch);

    if (StopwatchIsDone(*stopwatch))
    {
        StopwatchReset(stopwatch);
        *frame += 1;
    }

    *frame = *frame % maxFrames;

    DrawTexturePro(enemy->texture,
                   (Rectangle){frameWidth * (*frame), 0, frameWidth, enemy->texture.height},
                   (Rectangle){enemy->x, enemy->y, frameWidth * scaleFactor, enemy->texture.height * scaleFactor},
                   (Vector2){0, 0},
                   rotation,
                   RAYWHITE);
}