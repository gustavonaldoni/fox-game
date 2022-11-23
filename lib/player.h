typedef struct
{
    int x, y;
    Texture2D texture;
    int numberOfFrames;
    Rectangle hitbox;
} Player;

void CreatePlayer(Player *, int, int, Texture2D);
Rectangle CreatePlayerHitbox(Player *);
void UpdatePlayerHitbox(Player *);
