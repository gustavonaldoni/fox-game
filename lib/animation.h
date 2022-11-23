void AnimateTexture(Player* player, Stopwatch *stopwatch, int maxFrames, int *frame, float scaleFactor, Texture2D image)
{
    player->texture = image;
    float frameWidth = player->texture.width / maxFrames;

    StopwatchUpdate(stopwatch);

    if (StopwatchIsDone(*stopwatch))
    {
        StopwatchReset(stopwatch);
        *frame += 1;
    }
    
    *frame = *frame % maxFrames;
   

    DrawTexturePro(player->texture,
                   (Rectangle){frameWidth * (*frame), 0, frameWidth, player->texture.height},
                   (Rectangle){player->screenX, player->screenY, frameWidth * scaleFactor, player->texture.height * scaleFactor},
                   (Vector2){0, 0},
                   0.0f,
                   RAYWHITE);
}