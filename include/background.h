typedef struct
{
    Texture2D texture;
    int xMovement, yMovement;
    Stopwatch movementStopwatch;
} Background;

void CreateBackground(Background *, Texture2D);
void ShowBackground(Background);
void MoveBackground(Background *);
