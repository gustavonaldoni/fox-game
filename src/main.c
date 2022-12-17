// cc src/main.c -o build/a.out lib/*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Werror -I./include

/*
Integrantes:

Gustavo Naldoni
André Devecz
André Zappa
Rafael Leite
Daniel Pontes
Matheus Evangelista
*/

// Inclusão das bibliotecas necessárias
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "stopwatch.h"
#include "enemy.h"
#include "smoke.h"
#include "animation.h"
#include "collision.h"
#include "background.h"
#include "actionButton.h"
#include "score.h"
#include "deathScreen.h"
#include "list.h"
#include "volumeButton.h"
#include "numberOfRounds.h"

#define MAX_FPS 144
#define PLAYER_BASE_Y 310
#define PLAYER_BASE_Y_ATTACK 220

#define ATTACK_FREQUENCY 0.02f
#define DEFENSE_FREQUENCY 0.02f
#define RIGHT_FREQUENCY 0.08f
#define ENEMY_FREQUENCY 0.08f
#define SMOKE_FREQUENCY 0.2f

#define ATTACK_BUTTON_COOLDOWN 1.0f
#define DEFENSE_BUTTON_COOLDOWN 3.0f
#define HEAL_BUTTON_COOLDOWN 10.0f

#define MAX_VOLUME 1.0f
#define MIN_VOLUME 0.0f

#define ENEMY_APARISON_CONSTANT 400

#define FIRST_ROUND_ENEMIES 5

int pause = 0;
int checkedCollision = 0;
int numberOfRounds = 1;

int main(void)
{
  srand(time(NULL));

  InitWindow(1000, 600, "Fox Game");
  InitAudioDevice();

  // Criar lista dos inimigos
  ListLSE enemyList;
  ListLSECreate(&enemyList);

  Texture2D grayTexture = LoadTexture("../img/gray.png");

  Texture2D backgroundTexture = LoadTexture("../img/rCenario.png");
  Background background;
  CreateBackground(&background, backgroundTexture);

  Player player;
  Texture2D playerTextures[5] = {LoadTexture("../img/rDireita.png"), LoadTexture("../img/rAtaque.png"), LoadTexture("../img/foxHit.png"), LoadTexture("../img/foxDie.png"), LoadTexture("../img/foxBreathing.png")};
  CreatePlayer(&player, 100, PLAYER_BASE_Y, playerTextures[0], 7);
  CreatePlayerHitbox(&player);

  Texture2D enemyTextures[3] = {LoadTexture("../img/SlimeRtoL_Green.png"), LoadTexture("../img/SlimeRtoL_Red.png"), LoadTexture("../img/SlimeRtoL_Blue.png")};

  // Criação dos inimigos
  Enemy greenSlime;
  CreateEnemy(&greenSlime, GetScreenWidth() + ENEMY_APARISON_CONSTANT, 375, enemyTextures[0], 8, 100.0f, 1, 1, 1.0f);
  CreateEnemyHitbox(&greenSlime);

  Enemy blueSlime;
  CreateEnemy(&blueSlime, GetScreenWidth() + ENEMY_APARISON_CONSTANT, 375, enemyTextures[2], 8, 250.0f, 1, 2, 1.0f);
  CreateEnemyHitbox(&blueSlime);

  Enemy redSlime;
  CreateEnemy(&redSlime, GetScreenWidth() + ENEMY_APARISON_CONSTANT, 340, enemyTextures[1], 8, 80.0f, 2, 3, 1.5f);
  CreateEnemyHitbox(&redSlime);

  // Inserção de inimigos aleatórios na lista
  InsertRandomEnemies(&enemyList, FIRST_ROUND_ENEMIES, greenSlime, blueSlime, redSlime);

  Enemy *firstEnemy;
  firstEnemy = ListLSEInit(enemyList);

  Smoke smoke;
  Texture2D smokeTexture = LoadTexture("../img/slimeSmoke.png");
  CreateSmoke(&smoke, firstEnemy, smokeTexture, 7);

  // Criação dos botoẽs de ataque, defesa e cura
  ActionButton attackActionButton;
  CreateActionButton(&attackActionButton, 0, 0, LoadTexture("../img/botaoEspada.png"), LoadTexture("../img/botaoEspadaPreto.png"));

  ActionButton defenseActionButton;
  CreateActionButton(&defenseActionButton, 0, 0, LoadTexture("../img/botaoEscudo.png"), LoadTexture("../img/botaoEscudoPreto.png"));

  ActionButton potionActionButton;
  CreateActionButton(&potionActionButton, 0, 0, LoadTexture("../img/botaoPocao.png"), LoadTexture("../img/botaoPocaoPreto.png"));

  VolumeButton volumeButton;
  CreateVolumeButton(&volumeButton, LoadTexture("../img/botaoVolume.png"), LoadTexture("../img/botaoVolumeNone.png"));

  Texture2D playerHealth[2] = {LoadTexture("../img/rHealth.png"), LoadTexture("../img/rHealthDeath.png")};

  // Criação dos cronômetros necessários para as animações
  Stopwatch stopwatchRight = StopwatchCreate(RIGHT_FREQUENCY);
  Stopwatch stopwatchAttack = StopwatchCreate(ATTACK_FREQUENCY);
  Stopwatch stopwatchEnemy = StopwatchCreate(ENEMY_FREQUENCY);
  Stopwatch stopwatchSmoke = StopwatchCreate(SMOKE_FREQUENCY);

  Stopwatch stopwatchAttackButton = StopwatchCreate(ATTACK_BUTTON_COOLDOWN);
  Stopwatch stopwatchDefenseButton = StopwatchCreate(DEFENSE_BUTTON_COOLDOWN);
  Stopwatch stopwatchHealButton = StopwatchCreate(HEAL_BUTTON_COOLDOWN);

  Stopwatch actionButtonsStopwatches[3] = {stopwatchAttackButton, stopwatchDefenseButton, stopwatchHealButton};

  int frameRight = 0;
  int frameAttack = 0;
  int frameEnemy = 0;
  int frameSmoke = 0;

  // Música de fundo e som de ataque
  Sound slimeHitSound = LoadSound("../sounds/rSlimeHitSound.wav");

  Music backgroundMusic = LoadMusicStream("../sounds/xDeviruchi - Exploring The Unknown.wav");
  PlayMusicStream(backgroundMusic);

  SetTargetFPS(MAX_FPS);

  while (!WindowShouldClose())
  {
    if (player.isAttacking)
    {
      attackActionButton.isPressed = 1;
      StopwatchUpdate(&stopwatchAttackButton);

      if (StopwatchIsDone(stopwatchAttackButton))
      {
        StopwatchReset(&stopwatchAttackButton);
        player.isAttacking = 0;
      }
    }

    if (player.isDefending)
    {
      defenseActionButton.isPressed = 1;
      StopwatchUpdate(&stopwatchDefenseButton);

      if (StopwatchIsDone(stopwatchDefenseButton))
      {
        StopwatchReset(&stopwatchDefenseButton);
        player.isDefending = 0;
      }
    }

    if (player.isHealing)
    {
      potionActionButton.isPressed = 1;
      StopwatchUpdate(&stopwatchHealButton);

      if (StopwatchIsDone(stopwatchHealButton))
      {
        StopwatchReset(&stopwatchHealButton);
        player.isHealing = 0;
      }
    }

    actionButtonsStopwatches[0] = stopwatchAttackButton;
    actionButtonsStopwatches[1] = stopwatchDefenseButton;
    actionButtonsStopwatches[2] = stopwatchHealButton;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (ListLSEIsEmpty(enemyList))
    {
      InsertRandomEnemies(&enemyList, FIRST_ROUND_ENEMIES - 1 + numberOfRounds, greenSlime, blueSlime, redSlime);
      numberOfRounds++;
    }
    else
      firstEnemy = ListLSEInit(enemyList);

    MoveSmoke(&smoke, firstEnemy);
    AnimateSmokeTexture(&smoke, &stopwatchSmoke, smoke.numberOfFrames, &frameSmoke, 1.0f, smoke.texture);

    // Lógica do botão de volume
    if (UserClickedVolumeButton(volumeButton))
    {
      volumeButton.status = !volumeButton.status;

      if (volumeButton.status == 0)
        SetMasterVolume(MIN_VOLUME);
      else if (volumeButton.status == 1)
        SetMasterVolume(MAX_VOLUME);
    }

    ShowBackground(background);

    DrawPlayerHealth(player, playerHealth[0], playerHealth[1]);
    DrawScore(player.score);
    // DrawPlayerHitbox(player); // ONLY activate this for debbuging

    ActionButton actionButtons[3] = {attackActionButton, defenseActionButton, potionActionButton};
    DrawActionButtons(actionButtons, 3, actionButtonsStopwatches);

    DrawVolumeButton(volumeButton);

    DrawRoundNumber(numberOfRounds);

    // DrawEnemyHitbox(enemy); // ONLY activate this for debbuging

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

        if (IsPlayerDead(player))
        {
          player.numberOfFrames = 1;
          player.texture = playerTextures[3];
          AnimatePlayerTexture(&player, &stopwatchRight, player.numberOfFrames, &frameRight, 1.0f, player.texture);
        }
        else
          AnimatePlayerTexture(&player, &stopwatchRight, player.numberOfFrames, &frameRight, 1.0f, player.texture);
      }

      stopwatchEnemy.endSeconds += 1.0f;
      AnimateEnemyTexture(firstEnemy, &stopwatchEnemy, firstEnemy->numberOfFrames, &frameEnemy, firstEnemy->size, firstEnemy->texture);

      if (IsPlayerDead(player))
      {
        ListLSERemoveAll(&enemyList);
        InsertRandomEnemies(&enemyList, FIRST_ROUND_ENEMIES, greenSlime, blueSlime, redSlime);
        numberOfRounds = 1;

        DrawTexture(grayTexture, 0, 0, (Color){255, 255, 255, 200});
        DrawDeathScreenText();

        if (IsKeyPressed(KEY_SPACE))
        {
          player.score = 0;
          player.health = player.maxHealth;
          firstEnemy->x = GetScreenWidth() + ENEMY_APARISON_CONSTANT;
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

      // Animação de ataque dos inimigos
      if (firstEnemy->isAttacking == 1 && firstEnemy->x < 400)
      {
        firstEnemy->x += 10;
        firstEnemy->y -= 1;
        firstEnemy->currentSpeed = firstEnemy->baseSpeed;
      }
      else
      {
        firstEnemy->isAttacking = 0;
        if (firstEnemy->x < 300)
        {
          firstEnemy->currentSpeed = 450.0f;
          firstEnemy->y -= 2;
        }
      }

      if (firstEnemy->y != firstEnemy->baseY)
        firstEnemy->y += 1;

      MoveEnemy(firstEnemy);
      AnimateEnemyTexture(firstEnemy, &stopwatchEnemy, firstEnemy->numberOfFrames, &frameEnemy, firstEnemy->size, firstEnemy->texture);
      firstEnemy->currentSpeed = firstEnemy->baseSpeed;

      UpdatePlayerHitbox(&player);
      UpdateEnemyHitbox(firstEnemy);

      if (IsPlayerDead(player))
        pause = 1;

      if (CheckCollisionEnemyPlayer(*firstEnemy, player))
      {
        if (player.isAttacking)
        {
          UpdateScore(&player, 10);
          checkedCollision = 1;

          ListLSERemove(&enemyList, *firstEnemy);
        }
        else
        {
          firstEnemy->isAttacking = 1;
          PlaySound(slimeHitSound);

          if (!player.isDefending)
          {
            UpdatePlayerHealth(&player, -firstEnemy->damage);
            UpdateScore(&player, -1);
          }
        }
      }

      if (checkedCollision == 1 || checkedCollision == 2)
      {
        if (firstEnemy->x < GetScreenWidth() + 660 && checkedCollision == 2)
          checkedCollision = 0;

        if (checkedCollision != 0)
          checkedCollision = 2;
      }

      if (IsKeyPressed(KEY_A))
        player.isAttacking = 1;

      if (player.isAttacking)
      {
        player.texture = playerTextures[1];
        player.y = PLAYER_BASE_Y_ATTACK;
        player.numberOfFrames = 9;
        player.isAttacking = 1;

        AnimatePlayerTexture(&player, &stopwatchAttack, player.numberOfFrames, &frameAttack, 1.0f, player.texture);

        attackActionButton.isPressed = 1;
      }

      else
      {
        player.y = PLAYER_BASE_Y;
        player.isAttacking = 0;

        if (firstEnemy->isAttacking == 0 && firstEnemy->x > GetScreenWidth())
        {
          player.texture = playerTextures[0];
          player.numberOfFrames = 7;
          AnimatePlayerTexture(&player, &stopwatchRight, player.numberOfFrames, &frameRight, 1.0f, player.texture);
          MoveBackground(&background);
        }

        else if (firstEnemy->isAttacking == 0 && firstEnemy->x < GetScreenWidth())
        {
          player.texture = playerTextures[4];
          player.numberOfFrames = 8;
          AnimatePlayerTexture(&player, &stopwatchRight, player.numberOfFrames, &frameRight, 1.0f, player.texture);
        }
        else
        {
          player.texture = playerTextures[2];
          AnimatePlayerTexture(&player, &stopwatchAttack, 1, &frameAttack, 1.0f, player.texture);
        }

        if (IsKeyPressed(KEY_D) && player.isDefending == 0)
        {
          player.isDefending = 1;
        }
        else if (IsKeyPressed(KEY_C) && player.isHealing == 0)
        {
          player.isHealing = 1;
          UpdatePlayerHealth(&player, 1);
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
  UnloadTexture(playerTextures[2]);
  UnloadTexture(playerTextures[3]);
  UnloadTexture(playerTextures[4]);
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