#include "raylib.h"
#include "enemy.h"
#include "player.h"

void CreateEnemy(Enemy *enemy, int x, int y, Texture2D texture, int numberOfFrames)
{
    enemy->x = x;
    enemy->y = y;
    enemy->texture = texture;
}

void CreateEnemyHitbox(Enemy *enemy, Rectangle *hitbox)
{
    hitbox->x = enemy->x;
    hitbox->y = enemy->y;
    hitbox->width = enemy->texture.width / enemy->numberOfFrames;
    hitbox->height = enemy->texture.height / enemy->numberOfFrames;

    enemy->hitbox = *hitbox;
}

void UpdateEnemyHitbox(Enemy *enemy)
{
    enemy->hitbox.x = enemy->x;
    enemy->hitbox.y = enemy->y;
}

void DrawEnemyHitbox(Enemy enemy)
{
    DrawRectangleRec(enemy.hitbox, RED);
}
