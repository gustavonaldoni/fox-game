typedef struct
{
    Texture2D texture;
    int xMovement, yMovement;
    Stopwatch movementStopwatch;
    Color tint;
} Background;

void CreateBackground(Background *, Texture2D);
void ShowBackground(Background);
void MoveBackground(Background *);
