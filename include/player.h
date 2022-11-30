typedef struct
{
    int x, y;
    Texture2D texture;
    int numberOfFrames;
    int health, maxHealth;
    Rectangle hitbox;
} Player;

void CreatePlayer(Player *, int, int, Texture2D);
Rectangle CreatePlayerHitbox(Player *);
void UpdatePlayerHitbox(Player *);
void DrawPlayerHealth(Player, Texture2D, Texture2D);
