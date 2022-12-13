#include "raylib.h"
#include "actionButton.h"

void CreateActionButton(ActionButton *actionButton, int x, int y, Texture2D normalTexture, Texture2D pressedTexture)
{
  actionButton->x = x;
  actionButton->y = y;
  actionButton->normalTexture = normalTexture;
  actionButton->pressedTexture = pressedTexture;
  actionButton->isPressed = 0;
}

void DrawActionButton(ActionButton actionButton, float scaleFactor)
{
  float rotation;
  Vector2 position;

  rotation = 0.0f;

  position = (Vector2){actionButton.x, actionButton.y};

  if (actionButton.isPressed)
    DrawTextureEx(actionButton.pressedTexture, position, rotation, scaleFactor, RAYWHITE);
  else
    DrawTextureEx(actionButton.normalTexture, position, rotation, scaleFactor, RAYWHITE);
}

void DrawActionButtons(ActionButton actionButtons[], int numberOfButtons)
{
  int i, x, y, borderSpace, betweenButtonsSpace;
  float scaleFactor;

  borderSpace = 20;
  betweenButtonsSpace = 20;
  scaleFactor = 0.15f;

  x = borderSpace;
  y = GetScreenHeight() - (actionButtons[0].normalTexture.height * scaleFactor + borderSpace);

  for (i = 0; i < numberOfButtons; i++)
  {
    actionButtons[i].x = x;
    actionButtons[i].y = y;

    DrawActionButton(actionButtons[i], scaleFactor);

    x += betweenButtonsSpace + (actionButtons[0].normalTexture.width * scaleFactor);
  }
}

void ResetActionButton(ActionButton *actionButton)
{
  actionButton->isPressed = 0;
}

void UnloadActionButtonTextures(ActionButton *actionButton)
{
  UnloadTexture(actionButton->normalTexture);
  UnloadTexture(actionButton->pressedTexture);
}