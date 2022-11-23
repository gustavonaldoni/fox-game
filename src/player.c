#include "raylib.h"
#include "../lib/player.h"

void CreatePlayer(Player *Player, int screenX, int screenY, Texture2D texture)
{
  Player->id = 1;
  Player->screenX = screenX;
  Player->screenY = screenY;
  Player->texture = texture;
}
