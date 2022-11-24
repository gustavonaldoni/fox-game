// cc src/main.c -o build/a.out lib/*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Werror -I./include

#include "raylib.h"
#include "player.h"
#include "stopwatch.h"
#include "animation.h"
#include "enemy.h"
#include "collision.h"
#include "background.h"

#define MAX_FPS 144

int main(void)
{
    InitWindow(1000, 600, "Fox Game");

    Texture2D backgroundTexture = LoadTexture("../img/rCenario.png");
    Background background;
    CreateBackground(&background, backgroundTexture);

    Player player;
    Texture2D playerTextures[2] = {LoadTexture("../img/rDireita.png"), LoadTexture("../img/rAtaque.png")};
    CreatePlayer(&player, 100, 363, playerTextures[0]);

    Stopwatch stopwatchRight = StopwatchCreate(0.08f);
    Stopwatch stopwatchAttack = StopwatchCreate(0.02f);

    int frameRight = 0, frameAttack = 0;

    SetTargetFPS(MAX_FPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        MoveBackground(&background);
        ShowBackground(background);

        if (IsKeyDown(KEY_J))
        {   
            player.texture = playerTextures[1];
            player.y = 220;
            AnimatePlayerTexture(&player, &stopwatchAttack, 9, &frameAttack, 1.0f, player.texture);
        }
        else
        {
            player.texture = playerTextures[0];
            player.y = 310;
            AnimatePlayerTexture(&player, &stopwatchRight, 7, &frameRight, 1.0f, player.texture);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}