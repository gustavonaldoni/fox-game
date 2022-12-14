typedef struct
{
    int x, y;
    Texture2D volumeOnTexture, volumeOffTexture;
    int status;
    float scaleFactor;
} VolumeButton;

void CreateVolumeButton(VolumeButton *, Texture2D, Texture2D);
void DrawVolumeButton(VolumeButton);
int UserClickedVolumeButton(VolumeButton);
