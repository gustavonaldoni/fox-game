typedef struct
{
    int x, y;
    Texture2D texture;
    int numberOfFrames;
    float speed;
    Rectangle hitbox;
} Enemy;

void CreateEnemy(Enemy *, int, int, Texture2D, int, float);
void CreateEnemyHitbox(Enemy *);
void UpdateEnemyHitbox(Enemy *);
void DrawEnemyHitbox(Enemy);
void MoveEnemy(Enemy *);