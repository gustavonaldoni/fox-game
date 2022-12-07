typedef struct
{
    int x, y;
    Texture2D texture;
    int numberOfFrames;
    float speed;
    int damage;
    Rectangle hitbox;
} Enemy;

void CreateEnemy(Enemy *, int, int, Texture2D, int, float, int);
void CreateEnemyHitbox(Enemy *);
void UpdateEnemyHitbox(Enemy *);
void DrawEnemyHitbox(Enemy);
void MoveEnemy(Enemy *);