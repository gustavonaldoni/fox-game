#include "raylib.h"
#include "player.h"

void CreatePlayer(Player *player, int x, int y, Texture2D texture, int numberOfFrames)
{
  const int maxHealth = 5;

  player->x = x;
  player->y = y;
  player->texture = texture;
  player->maxHealth = maxHealth;
  player->health = player->maxHealth;
  player->numberOfFrames = numberOfFrames;
}

void CreatePlayerHitbox(Player *player)
{
  Rectangle hitbox;

  hitbox.x = player->x;
  hitbox.y = player->y;
  hitbox.width = (player->texture.width / player->numberOfFrames);
  hitbox.height = player->texture.height;

  player->hitbox = hitbox;
}

void UpdatePlayerHitbox(Player *player)
{
  player->hitbox.x = player->x;
  player->hitbox.y = player->y;
  player->hitbox.width = (player->texture.width / player->numberOfFrames) - 60;
  player->hitbox.height = player->texture.height;
}

void DrawPlayerHitbox(Player player)
{
  DrawRectangleRec(player.hitbox, RED);
}

void DrawPlayerHealth(Player player, Texture2D healthTexture, Texture2D deathTexture)
{
  int i, x, y, borderSpace, betweenHealthSpace;
  float scaleFactor, rotation;

  borderSpace = 10;
  betweenHealthSpace = 5;
  scaleFactor = 1.2f;
  rotation = 0.0f;

  x = borderSpace;
  y = borderSpace;

  for (i = 0; i < player.maxHealth; i++)
  {
    if (i + 1 <= player.health)
      DrawTextureEx(healthTexture, (Vector2){x, y}, rotation, scaleFactor, RAYWHITE);
    else
      DrawTextureEx(deathTexture, (Vector2){x, y}, rotation, scaleFactor, RAYWHITE);

    x += betweenHealthSpace + healthTexture.width;
  }
}
