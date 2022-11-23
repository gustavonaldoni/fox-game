#include "raylib.h"
#include "player.h"

void CreatePlayer(Player *Player, int screenX, int screenY, Texture2D texture)
{
  Player->id = 1;
  Player->screenX = screenX;
  Player->screenY = screenY;
  Player->texture = texture;
}
