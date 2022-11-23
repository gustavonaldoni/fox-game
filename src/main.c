// cc src/main.c -o build/a.out include/*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Werror -I./lib

#include "raylib.h"
#include "player.h"
#include "stopwatch.h"
#include "animation.h"
#include "enemy.h"
#include "collision.h"

int main(void)
{
    InitWindow(1000, 600, "Fox Game");

    Texture2D background = LoadTexture("../img/rCenario.png");
    Texture2D playerTextures[2] = {LoadTexture("../img/rDireita.png"), LoadTexture("../img/rAtaque.png")};

    Stopwatch stopwatchRight = StopwatchCreate(0.08f);
    Stopwatch stopwatchAttack = StopwatchCreate(0.02f);
    Player player;

    CreatePlayer(&player, 100, 363, playerTextures[0]);

    int frameRight = 0, frameAttack = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, 5.1f, RAYWHITE);

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