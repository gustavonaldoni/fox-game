#define MAX_VOLUME 1.0f
#define MIN_VOLUME 0.0f

typedef struct
{
    int x, y;
    int width, height;
    float volume;
    Rectangle lineRectangle, filledRectangle;
    Color color;
} VolumeBar;

void CreateVolumeBar(VolumeBar *, int, int, int, int);
bool UserHasClickedOnVolumeBar(VolumeBar);
void UpdateVolumeBar(VolumeBar *, float *);
void DrawVolumeBar(VolumeBar);
