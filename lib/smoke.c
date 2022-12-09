#include "raylib.h"
#include "enemy.h"
#include "smoke.h"

void CreateSmoke(Smoke *smoke, Enemy *enemy, Texture2D texture, int numberOfFrames)
{
  smoke->x = enemy->x;
  smoke->y = enemy->y;
  smoke->texture = texture;
  smoke->numberOfFrames = numberOfFrames;
}

void MoveSmoke(Smoke *smoke, Enemy *enemy)
{
    smoke->x = enemy->x;
    smoke->y = smoke->y;
}