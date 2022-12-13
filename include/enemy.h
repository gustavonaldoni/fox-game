typedef struct
{
    int id;
    int x, y;
    Texture2D texture;
    int numberOfFrames;
    float speed;
    int damage;
    int isAttacking;
    Rectangle hitbox;
} Enemy;

void CreateEnemy(Enemy *, int, int, Texture2D, int, float, int, int);
void CreateEnemyHitbox(Enemy *);
void UpdateEnemyHitbox(Enemy *);
void DrawEnemyHitbox(Enemy);
void MoveEnemy(Enemy *);