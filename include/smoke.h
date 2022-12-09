typedef struct
{
    int x, y;
    Texture2D texture;
    int numberOfFrames;
    float speed;
} Smoke;

void CreateSmoke(Smoke *, Enemy *, Texture2D, int);
void MoveSmoke(Smoke *, Enemy *);