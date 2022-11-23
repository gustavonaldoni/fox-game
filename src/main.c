#include "raylib.h"
#include "../lib/players.h"
#include "../lib/stopwatch.h"
#include "../lib/animation.h"

// Compile with: cc src/*.c -o build/a.out -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Werror

int main(void)
{
    InitWindow(1000, 600, "Fox Game");

    Texture2D background = LoadTexture("../img/rCenario.png");
    Texture2D playerTextures[2] = {LoadTexture("../img/rDireita.png"), LoadTexture("../img/rAtaque.png")};

    Stopwatch stopwatchRight = StopwatchCreate(0.08f);
    Stopwatch stopwatchAttack = StopwatchCreate(0.04f);
    Player player;

    createPlayer(&player, 100, 363, playerTextures[0]);

    int frameRight = 0, frameAttack = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, 5.1f, RAYWHITE);

        if (IsKeyDown(KEY_J))
        {   
            player.texture = playerTextures[1];
            player.screenY = 273;
            AnimateTexture(&player, &stopwatchAttack, 10, &frameAttack, 1.0f, player.texture);
        }
        else
        {
            player.texture = playerTextures[0];
            player.screenY = 363;
            AnimateTexture(&player, &stopwatchRight, 7, &frameRight, 1.0f, player.texture);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}