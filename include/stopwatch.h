typedef struct
{
    float endSeconds;
    float currentSeconds;
} Stopwatch;

Stopwatch StopwatchCreate(float);
void StopwatchReset(Stopwatch *);
bool StopwatchIsDone(Stopwatch);
void StopwatchUpdate(Stopwatch *);
