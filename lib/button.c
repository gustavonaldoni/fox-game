#include "raylib.h"

void actionButton(Texture2D attackButton[], Texture2D defenseButton[], Texture2D potionButton[], int pressButton)
{
   if(pressButton == 1)
   {
     DrawTexture(attackButton[1], 30, 550, WHITE);
     DrawTexture(defenseButton[0], 100, 550, WHITE);
     DrawTexture(potionButton[0], 170, 550, WHITE);
   }

   else if(pressButton == 2)
   {
     DrawTexture(attackButton[0], 30, 550, WHITE);
     DrawTexture(defenseButton[1], 100, 550, WHITE);
     DrawTexture(potionButton[0], 170, 550, WHITE);
   }

   else if(pressButton == 3)
   {
     DrawTexture(attackButton[0], 30, 550, WHITE);
     DrawTexture(defenseButton[0], 100, 550, WHITE);
     DrawTexture(potionButton[1], 170, 550, WHITE);
   }
   else
   {
     DrawTexture(attackButton[0], 30, 550, WHITE);
     DrawTexture(defenseButton[0], 100, 550, WHITE);
     DrawTexture(potionButton[0], 170, 550, WHITE);
   }
}