typedef struct
{
    int id;
    int screenX;
    int screenY;
    Texture2D texture;
} Player;

void CreatePlayer(Player *, int, int, Texture2D);
