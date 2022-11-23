#include <stdbool.h>
#include "raylib.h"
#include "player.h"
#include "enemy.h"

bool CheckCollisionEnemyPlayer(Enemy enemy, Player player)
{
    return CheckCollisionRecs(enemy.hitbox, player.hitbox);
}