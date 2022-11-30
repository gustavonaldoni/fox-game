#include "raylib.h"
#include "player.h"

void CreatePlayer(Player *player, int x, int y, Texture2D texture)
{
  const int maxHealth = 5;

  player->x = x;
  player->y = y;
  player->texture = texture;
  player->maxHealth = maxHealth;
  player->health = player->maxHealth;
}

Rectangle CreatePlayerHitbox(Player *player)
{
  Rectangle rectangle;

  rectangle.x = player->x;
  rectangle.y = player->y;
  rectangle.width = player->texture.width / player->numberOfFrames;
  rectangle.height = player->texture.height / player->numberOfFrames;

  return rectangle;
}

void UpdatePlayerHitbox(Player *player)
{
  player->hitbox.x = player->x;
  player->hitbox.y = player->y;
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
