#include "raylib.h"
#include "volumeButton.h"

void CreateVolumeButton(VolumeButton *volumeButton, Texture2D volumeOnTexture, Texture2D volumeOffTexture)
{
    volumeButton->x = 23;
    volumeButton->y = 70;
    volumeButton->volumeOnTexture = volumeOnTexture;
    volumeButton->volumeOffTexture = volumeOffTexture;
    volumeButton->status = 1;
    volumeButton->scaleFactor = 0.09f;
}

void DrawVolumeButton(VolumeButton volumeButton)
{
    const float rotation = 0.0f;
    Texture2D correctTexture;

    if (volumeButton.status == 1)
        correctTexture = volumeButton.volumeOnTexture;
    else if (volumeButton.status == 0)
        correctTexture = volumeButton.volumeOffTexture;

    DrawTextureEx(correctTexture, (Vector2){volumeButton.x, volumeButton.y}, rotation, volumeButton.scaleFactor, WHITE);
}

int UserClickedVolumeButton(VolumeButton volumeButton)
{
    Rectangle buttonRectangle;

    buttonRectangle = (Rectangle){volumeButton.x, volumeButton.y, volumeButton.volumeOnTexture.width * volumeButton.scaleFactor, volumeButton.volumeOnTexture.height * volumeButton.scaleFactor};

    return CheckCollisionPointRec(GetMousePosition(), buttonRectangle) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}