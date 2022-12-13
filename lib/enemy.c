#include "raylib.h"
#include "enemy.h"

void CreateEnemy(Enemy *enemy, int x, int y, Texture2D texture, int numberOfFrames, float speed, int damage, int id, float size)
{
    enemy->id = id;
    enemy->x = x;
    enemy->y = y;
    enemy->baseY = enemy->y;
    enemy->texture = texture;
    enemy->numberOfFrames = numberOfFrames;
    enemy->baseSpeed = speed;
    enemy->currentSpeed = enemy->baseSpeed;
    enemy->damage = damage;
    enemy->size = size;
    enemy->isAttacking = 0;
}

void CreateEnemyHitbox(Enemy *enemy)
{
    Rectangle hitbox;

    hitbox.x = enemy->x;
    hitbox.y = enemy->y;
    hitbox.width = enemy->texture.width / enemy->numberOfFrames;
    hitbox.height = enemy->texture.height;

    enemy->hitbox = hitbox;
}

void UpdateEnemyHitbox(Enemy *enemy)
{
    enemy->hitbox.x = enemy->x;
    enemy->hitbox.y = enemy->y;
    enemy->hitbox.width = enemy->texture.width / enemy->numberOfFrames;
    enemy->hitbox.height = enemy->texture.height;
}

void DrawEnemyHitbox(Enemy enemy)
{
    DrawRectangleRec(enemy.hitbox, RED);
}

void MoveEnemy(Enemy *enemy)
{
    enemy->x -= enemy->currentSpeed * GetFrameTime();
}
