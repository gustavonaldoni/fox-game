#include "raylib.h"
#include "player.h"

void CreatePlayer(Player *Player, int x, int y, Texture2D texture)
{
  Player->x = x;
  Player->y = y;
  Player->texture = texture;
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
