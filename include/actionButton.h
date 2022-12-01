typedef struct
{
    int x, y;
    Texture2D normalTexture, pressedTexture;
    int isPressed;
} ActionButton;

void CreateActionButton(ActionButton *, int, int, Texture2D, Texture2D);
void DrawActionButton(ActionButton, float);
void DrawActionButtons(ActionButton *, int);
void ResetActionButton(ActionButton *);
void UnloadActionButtonTextures(ActionButton *);
