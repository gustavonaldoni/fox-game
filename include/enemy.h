typedef struct
{
    int x, y;
    Texture2D texture;
    int numberOfFrames;
    Rectangle hitbox;
} Enemy;

void CreateEnemy(Enemy *, int, int, Texture2D, int);
void CreateEnemyHitbox(Enemy *, Rectangle *);
void UpdateEnemyHitbox(Enemy *);
void DrawEnemyHitbox(Enemy);