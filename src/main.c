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
#include "score.h"
#include "deathScreen.h"

#define MAX_FPS 144
#define PLAYER_BASE_Y 310

#define ATTACK_FREQUENCY 0.02f
#define RIGHT_FREQUENCY 0.08f
#define ENEMY_FREQUENCY 0.08f

int pause = 0;

int main(void)
{
  InitWindow(1000, 600, "Fox Game");
  InitAudioDevice();

  Texture2D grayTexture = LoadTexture("../img/gray.png");

  Texture2D backgroundTexture = LoadTexture("../img/rCenario.png");
  Background background;
  CreateBackground(&background, backgroundTexture);

  Player player;
  Texture2D playerTextures[2] = {LoadTexture("../img/rDireita.png"), LoadTexture("../img/rAtaque.png")};
  CreatePlayer(&player, 100, PLAYER_BASE_Y, playerTextures[0], 7);
  CreatePlayerHitbox(&player);

  Enemy enemy;
  CreateEnemy(&enemy, 900, 375, LoadTexture("../img/SlimeRtoL.png"), 8, 100.0f, 1);
  CreateEnemyHitbox(&enemy);

  ActionButton attackActionButton;
  CreateActionButton(&attackActionButton, 0, 0, LoadTexture("../img/rAttackButton.png"), LoadTexture("../img/rPressedAttackButton.png"));

  ActionButton defenseActionButton;
  CreateActionButton(&defenseActionButton, 0, 0, LoadTexture("../img/rDefenseButton.png"), LoadTexture("../img/rPressedDefenseButton.png"));

  ActionButton potionActionButton;
  CreateActionButton(&potionActionButton, 0, 0, LoadTexture("../img/rPotionButton.png"), LoadTexture("../img/rPressedPotionButton.png"));

  Texture2D playerHealth[2] = {LoadTexture("../img/rHealth.png"), LoadTexture("../img/rHealthDeath.png")};

  Stopwatch stopwatchRight = StopwatchCreate(RIGHT_FREQUENCY);
  Stopwatch stopwatchAttack = StopwatchCreate(ATTACK_FREQUENCY);
  Stopwatch stopwatchEnemy = StopwatchCreate(ENEMY_FREQUENCY);

  int frameRight = 0;
  int frameAttack = 0;
  int frameEnemy = 0;

  Sound slimeHitSound = LoadSound("../sounds/rSlimeHitSound.wav");

  Music backgroundMusic = LoadMusicStream("../sounds/xDeviruchi - Exploring The Unknown.wav");
  PlayMusicStream(backgroundMusic);

  SetTargetFPS(MAX_FPS);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    ShowBackground(background);

    DrawPlayerHealth(player, playerHealth[0], playerHealth[1]);
    DrawScore(player.score);
    // DrawPlayerHitbox(player); // ONLY activate this for debbuging

    ActionButton actionButtons[3] = {attackActionButton, defenseActionButton, potionActionButton};
    DrawActionButtons(actionButtons, 3);

    // DrawEnemyHitbox(enemy); // ONLY activate this for debbuging

    if (IsKeyPressed(KEY_K))
      pause = !pause;

    if (pause == 1)
    {
      if (player.isAttacking)
      {
        player.texture = playerTextures[1];
        player.y = 220;
        player.numberOfFrames = 9;

        stopwatchAttack.endSeconds += 1.0f;

        AnimatePlayerTexture(&player, &stopwatchAttack, player.numberOfFrames, &frameAttack, 1.0f, player.texture);
      }
      else
      {
        player.texture = playerTextures[0];
        player.numberOfFrames = 7;
        player.y = PLAYER_BASE_Y;

        stopwatchRight.endSeconds += 1.0f;

        AnimatePlayerTexture(&player, &stopwatchRight, player.numberOfFrames, &frameRight, 1.0f, player.texture);
      }

      stopwatchEnemy.endSeconds += 1.0f;
      AnimateEnemyTexture(&enemy, &stopwatchEnemy, enemy.numberOfFrames, &frameEnemy, 1.0f, enemy.texture);

      if (IsPlayerDead(player))
      {
        DrawTexture(grayTexture, 0, 0, (Color){255, 255, 255, 200});
        DrawDeathScreenText();

        if (IsKeyPressed(KEY_SPACE))
        {
          player.score = 0;
          player.health = player.maxHealth;
          enemy.x = GetScreenWidth() - enemy.texture.width / enemy.numberOfFrames;
          pause = 0;
        }
      }
    }
    else
    {
      stopwatchRight.endSeconds = RIGHT_FREQUENCY;
      stopwatchAttack.endSeconds = ATTACK_FREQUENCY;
      stopwatchEnemy.endSeconds = ENEMY_FREQUENCY;

      UpdateMusicStream(backgroundMusic);

      if (!IsMusicStreamPlaying(backgroundMusic))
        PlayMusicStream(backgroundMusic);

      MoveBackground(&background);

      MoveEnemy(&enemy);
      AnimateEnemyTexture(&enemy, &stopwatchEnemy, enemy.numberOfFrames, &frameEnemy, 1.0f, enemy.texture);

      UpdatePlayerHitbox(&player);
      UpdateEnemyHitbox(&enemy);

      if (IsPlayerDead(player))
        pause = 1;

      if (CheckCollisionEnemyPlayer(enemy, player))
      {
        if (player.isAttacking)
        {
          enemy.x += GetScreenWidth() - 20;
          UpdateScore(&player, 10);
        }

        else
        {
          enemy.x += 300;
          PlaySound(slimeHitSound);
          UpdatePlayerHealth(&player, -enemy.damage);
          UpdateScore(&player, -1);
        }
      }

      if (IsKeyDown(KEY_A))
      {
        player.texture = playerTextures[1];
        player.y = 220;
        player.numberOfFrames = 9;
        player.isAttacking = 1;

        AnimatePlayerTexture(&player, &stopwatchAttack, player.numberOfFrames, &frameAttack, 1.0f, player.texture);

        attackActionButton.isPressed = 1;
      }

      else
      {
        player.texture = playerTextures[0];
        player.numberOfFrames = 7;
        player.y = PLAYER_BASE_Y;
        player.isAttacking = 0;

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

  UnloadSound(slimeHitSound);
  UnloadMusicStream(backgroundMusic);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}