typedef struct
{
    int id;
    int screenX;
    int screenY;
    Texture2D texture;
} Player;

void createPlayer(Player *Player, int screenX, int screenY, Texture2D texture)
{
  Player->id = 1;
  Player->screenX = screenX;
  Player->screenY = screenY;
  Player->texture = texture;
}