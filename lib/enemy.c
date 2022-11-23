#include "raylib.h"
#include "enemy.h"
#include "player.h"

void CreateEnemy(Enemy *enemy, int x, int y, Texture2D texture, int numberOfFrames)
{
    enemy->x = x;
    enemy->y = y;
    enemy->texture = texture;
}

Rectangle CreateEnemyHitbox(Enemy *enemy)
{
    Rectangle rectangle;

    rectangle.x = enemy->x;
    rectangle.y = enemy->y;
    rectangle.width = enemy->texture.width / enemy->numberOfFrames;
    rectangle.height = enemy->texture.height / enemy->numberOfFrames;

    return rectangle;
}

void UpdateEnemyHitbox(Enemy *enemy)
{
    enemy->hitbox.x = enemy->x;
    enemy->hitbox.y = enemy->y;
}
