// cc src/main.c -o build/a.out lib/*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Werror -I./include

#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "stopwatch.h"
#include "enemy.h"
#include "animation.h"
#include "collision.h"
#include "background.h"
#include "actionButton.h"

#define MAX_FPS 144
#define PLAYER_BASE_Y 310

int main(void)
{
  InitWindow(1000, 600, "Fox Game");

  Texture2D backgroundTexture = LoadTexture("../img/rCenario.png");
  Background background;
  CreateBackground(&background, backgroundTexture);

  Player player;
  Texture2D playerTextures[2] = {LoadTexture("../img/rDireita.png"), LoadTexture("../img/rAtaque.png")};
  CreatePlayer(&player, 100, PLAYER_BASE_Y, playerTextures[0], 7);
  CreatePlayerHitbox(&player);

  Enemy enemy;
  CreateEnemy(&enemy, 900, 375, LoadTexture("../img/SlimeRtoL.png"), 8, 100.0f);
  CreateEnemyHitbox(&enemy);

  ActionButton attackActionButton;
  CreateActionButton(&attackActionButton, 0, 0, LoadTexture("../img/rAttackButton.png"), LoadTexture("../img/rPressedAttackButton.png"));

  ActionButton defenseActionButton;
  CreateActionButton(&defenseActionButton, 0, 0, LoadTexture("../img/rDefenseButton.png"), LoadTexture("../img/rPressedDefenseButton.png"));

  ActionButton potionActionButton;
  CreateActionButton(&potionActionButton, 0, 0, LoadTexture("../img/rPotionButton.png"), LoadTexture("../img/rPressedPotionButton.png"));

  Texture2D playerHealth[2] = {LoadTexture("../img/rHealth.png"), LoadTexture("../img/rHealthDeath.png")};

  Stopwatch stopwatchRight = StopwatchCreate(0.08f);
  Stopwatch stopwatchAttack = StopwatchCreate(0.02f);
  Stopwatch stopwatchEnemy = StopwatchCreate(0.08f);

  int frameRight = 0;
  int frameAttack = 0;
  int frameEnemy = 0;

  SetTargetFPS(MAX_FPS);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    MoveBackground(&background);
    ShowBackground(background);

    DrawPlayerHealth(player, playerHealth[0], playerHealth[1]);
    UpdatePlayerHitbox(&player);
    // DrawPlayerHitbox(player); // ONLY activate this for debbuging

    ActionButton actionButtons[3] = {attackActionButton, defenseActionButton, potionActionButton};
    DrawActionButtons(actionButtons, 3);

    UpdateEnemyHitbox(&enemy);
    // DrawEnemyHitbox(enemy); // ONLY activate this for debbuging
    MoveEnemy(&enemy);
    AnimateEnemyTexture(&enemy, &stopwatchEnemy, enemy.numberOfFrames, &frameEnemy, 1.0f, enemy.texture);

    if (CheckCollisionEnemyPlayer(enemy, player))
    {
      enemy.x += 200;
      UpdatePlayerHealth(&player, -1);
    }

    if (IsKeyDown(KEY_A))
    {
      player.texture = playerTextures[1];
      player.y = 220;
      player.numberOfFrames = 9;
      AnimatePlayerTexture(&player, &stopwatchAttack, player.numberOfFrames, &frameAttack, 1.0f, player.texture);

      attackActionButton.isPressed = 1;
    }

    else
    {
      player.texture = playerTextures[0];
      player.numberOfFrames = 7;
      player.y = PLAYER_BASE_Y;

      AnimatePlayerTexture(&player, &stopwatchRight, player.numberOfFrames, &frameRight, 1.0f, player.texture);

      if (IsKeyDown(KEY_D))
      {
        defenseActionButton.isPressed = 1;
      }
      else if (IsKeyDown(KEY_C))
      {
        potionActionButton.isPressed = 1;
      }
      else
      {
        ResetActionButton(&attackActionButton);
        ResetActionButton(&defenseActionButton);
        ResetActionButton(&potionActionButton);
      }
    }

    EndDrawing();
  }

  UnloadTexture(backgroundTexture);
  UnloadTexture(background.texture);
  UnloadTexture(playerTextures[0]);
  UnloadTexture(playerTextures[1]);
  UnloadTexture(player.texture);

  UnloadActionButtonTextures(&attackActionButton);
  UnloadActionButtonTextures(&defenseActionButton);
  UnloadActionButtonTextures(&potionActionButton);

  CloseWindow();
  return 0;
}