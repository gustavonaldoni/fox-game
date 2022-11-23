#include "raylib.h"
#include "player.h"

void CreatePlayer(Player *Player, int x, int y, Texture2D texture)
{
  Player->x = x;
  Player->y = y;
  Player->texture = texture;
}
