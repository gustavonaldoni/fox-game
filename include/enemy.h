typedef struct
{
    int id;
    int x, y;
    int baseY;
    Texture2D texture;
    int numberOfFrames;
    float baseSpeed, currentSpeed;
    int damage;
    float size;
    int isAttacking;
    Rectangle hitbox;
} Enemy;

void CreateEnemy(Enemy *, int, int, Texture2D, int, float, int, int, float);
void CreateEnemyHitbox(Enemy *);
void UpdateEnemyHitbox(Enemy *);
void DrawEnemyHitbox(Enemy);
void MoveEnemy(Enemy *);