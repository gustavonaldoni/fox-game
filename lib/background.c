#include "raylib.h"
#include "background.h"

void CreateBackground(Background *background, Texture2D texture)
{
    background->texture = texture;
}

void ShowBackground(Background background)
{
    const float rotation = 0.0f, scaleFactor = 5.1f;
    
    DrawTextureEx(background.texture, (Vector2){0, 0}, rotation, scaleFactor, RAYWHITE);
}