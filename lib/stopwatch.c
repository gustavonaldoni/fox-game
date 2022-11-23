#include <stdbool.h>
#include "stopwatch.h"
#include "raylib.h"

Stopwatch StopwatchCreate(float endSeconds)
{
    Stopwatch stopwatch;

    stopwatch.currentSeconds = 0.0f;
    stopwatch.endSeconds = endSeconds;

    return stopwatch;
}

void StopwatchReset(Stopwatch *stopwatch)
{
    stopwatch->currentSeconds = 0.0f;
}

bool StopwatchIsDone(Stopwatch stopwatch)
{
    return stopwatch.currentSeconds >= stopwatch.endSeconds;
}

void StopwatchUpdate(Stopwatch *stopwatch)
{
    if (!StopwatchIsDone(*stopwatch))
    {
        stopwatch->currentSeconds += GetFrameTime();
    }
}