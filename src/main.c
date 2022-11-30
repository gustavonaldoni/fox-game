// cc src/main.c -o build/a.out lib/*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Werror -I./include

#include "raylib.h"
#include "player.h"
#include "stopwatch.h"
#include "enemy.h"
#include "animation.h"
#include "collision.h"
#include "background.h"
#include "button.h"

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

  Enemy enemy;
  Texture2D enemyTexture[1] = {LoadTexture("../img/SlimeRtoL.png")};
  CreateEnemy(&enemy, 900, 363, enemyTexture[0], 2);

  Texture2D attackButton[2] = {LoadTexture("../img/rAttackButton.png"), LoadTexture("../img/rPressedAttackButton.png")};
  Texture2D defenseButton[2] = {LoadTexture("../img/rDefenseButton.png"), LoadTexture("../img/rPressedDefenseButton.png")};
  Texture2D potionButton[2] = {LoadTexture("../img/rPotionButton.png"), LoadTexture("../img/rPressedPotionButton.png")};
  Texture2D playerHealth[2] = {LoadTexture("../img/rHealth.png"), LoadTexture("../img/rHealthDeath.png")};

  Stopwatch stopwatchRight = StopwatchCreate(0.08f);
  Stopwatch stopwatchAttack = StopwatchCreate(0.02f);
  Stopwatch stopwatchEnemy = StopwatchCreate(0.08);

  int frameRight = 0, frameAttack = 0, frameEnemy = 0;

  SetTargetFPS(MAX_FPS);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    MoveBackground(&background);
    ShowBackground(background);

    enemy.texture = enemyTexture[0];
    enemy.y = 375;
    AnimateEnemyTexture(&enemy, &stopwatchEnemy, 8, &frameEnemy, 1.0f, enemy.texture);

    DrawPlayerHealth(player, playerHealth[0], playerHealth[1]);

    if (IsKeyDown(KEY_A))
    {
      player.texture = playerTextures[1];
      player.y = 220;
      AnimatePlayerTexture(&player, &stopwatchAttack, 9, &frameAttack, 1.0f, player.texture);
      actionButton(attackButton, defenseButton, potionButton, 1);
    }
    else
    {
      player.texture = playerTextures[0];
      player.y = 310;
      AnimatePlayerTexture(&player, &stopwatchRight, 7, &frameRight, 1.0f, player.texture);

      if (IsKeyDown(KEY_D))
      {
        actionButton(attackButton, defenseButton, potionButton, 2);
      }
      else if (IsKeyDown(KEY_C))
      {
        actionButton(attackButton, defenseButton, potionButton, 3);
      }
      else
      {
        actionButton(attackButton, defenseButton, potionButton, 0);
      }
    }

    EndDrawing();
  }

  UnloadTexture(backgroundTexture);
  UnloadTexture(background.texture);
  UnloadTexture(playerTextures[0]);
  UnloadTexture(playerTextures[1]);

  CloseWindow();

  return 0;
}