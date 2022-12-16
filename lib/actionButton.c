#include <stdlib.h>
#include "raylib.h"
#include "stopwatch.h"
#include "actionButton.h"

void CreateActionButton(ActionButton *actionButton, int x, int y, Texture2D normalTexture, Texture2D pressedTexture)
{
  actionButton->x = x;
  actionButton->y = y;
  actionButton->normalTexture = normalTexture;
  actionButton->pressedTexture = pressedTexture;
  actionButton->isPressed = 0;
}

void DrawActionButton(ActionButton actionButton, float scaleFactor, Stopwatch *stopwatch)
{
  float rotation = 0.0f;
  Vector2 position = {0};

  const char *cooldownText = NULL;
  int xText = 0, yText = 0;
  Vector2 textPosition = {0};
  float textWidth = 0.0f, textHeight = 0.0f;
  float fontSize = 20.0f;
  float spacing = 5.0f;
  float remainingSeconds = 0.0f;

  position = (Vector2){actionButton.x, actionButton.y};

  remainingSeconds = stopwatch->endSeconds - stopwatch->currentSeconds;
  cooldownText = TextFormat("%.1f", remainingSeconds);

  textWidth = MeasureTextEx(GetFontDefault(), cooldownText, fontSize, spacing).x;
  textHeight = MeasureTextEx(GetFontDefault(), cooldownText, fontSize, spacing).y;

  xText = actionButton.x + (actionButton.normalTexture.width * scaleFactor - textWidth) / 2;
  yText = actionButton.y + (actionButton.normalTexture.height * scaleFactor - textHeight) / 2;
  textPosition = (Vector2){xText, yText};

  if (actionButton.isPressed)
  {
    DrawTextureEx(actionButton.pressedTexture, position, rotation, scaleFactor, RAYWHITE);
    DrawTextEx(GetFontDefault(), cooldownText, textPosition, fontSize, spacing, RAYWHITE);
  }
  else
    DrawTextureEx(actionButton.normalTexture, position, rotation, scaleFactor, RAYWHITE);
}

void DrawActionButtons(ActionButton actionButtons[], int numberOfButtons, Stopwatch stopwatches[])
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

    DrawActionButton(actionButtons[i], scaleFactor, &stopwatches[i]);

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