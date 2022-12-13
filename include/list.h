struct Node
{
    Enemy enemy;
    struct Node *next;
};

typedef struct
{
    struct Node *init;
    struct Node *end;
} ListLSE;

void ListLSECreate(ListLSE *);
bool ListLSEIsEmpty(ListLSE);

bool ListLSEInsertEnd(ListLSE *, Enemy);

int ListLSECountElements(ListLSE);

int ListLSERemove(ListLSE *list, Enemy);

Enemy *ListLSEInit(ListLSE);
void InsertRandomEnemies(ListLSE *, int, Enemy, Enemy, Enemy);