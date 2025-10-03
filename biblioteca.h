/*ARGHIR Elisa-Elena*/

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

//structura pentru un satelit, care contine nume si frecventa
typedef struct Satellite {
    char *name;
    int fr; 
}Satellite;

//structura pentru un nod din arbore, care contine un satelit
typedef struct node {
    Satellite elem;
    struct node *lt, *rt;
}TreeNode, *TTree;

/*structura pentru minHeap care contine dimensiunea maxima, adica
nr de sateliti, nr actual de elemente si elementele care sunt 
noduri ale unui arbore*/
typedef struct {
    int maxHeapSize; 
    int size;
    TreeNode **elem; 
}PrQueue, *APrQueue;

//structura pentru coada, pentru afisarea pe nivel, la cerinta 1
typedef struct cell{
    TTree elem;
    struct cell *next;
}QueueCell, *PQueue;

//structura pentru a gestiona coada 
typedef struct Queue {
    PQueue front;
    PQueue rear;
} *AQueue;

//structura pentru stiva, cu care parcurg DFS de la cerinta 3, 
//in care am adaugat si path, care imi retine calea pentru fiecare satelit
typedef struct stack_cell {
    TTree elem;
    //1001 deoarece codificarea e un sir de cel max 1000 caractere
    char path[1001]; 
    struct stack_cell *next;
}Stack, *PStack;

//-----------------CERINTA 1-----------------

void PQInit(APrQueue q, int maxSize);
void Insert(APrQueue q, TreeNode *node);
void SiftDown(APrQueue q, int i);
void SiftUp(APrQueue q, int i);
TreeNode *ExtractMin(APrQueue q);
TTree buildNod(Satellite a, TTree ltree, TTree rtree);
AQueue initQueue();
int isEmptyQueue(AQueue q);
void enqueue(AQueue p, TTree a);
TTree dequeue(AQueue p);
void printBFS(TTree tree, FILE *f);

//-----------------CERINTA 2-----------------

void task2(int nr, FILE *f, FILE *out, TTree root);

//-----------------CERINTA 3-----------------

PStack initStack();
int isEmptyStack(PStack s);
PStack push(PStack s, TTree a, char *path);
PStack pop(PStack s, TTree *a, char *path);
void browseDFS(TTree root, char *name, char *encoding);
void task3(int nr, FILE *f, FILE *out, TTree root);

//-----------------CERINTA 4-----------------

PStack push_task4(PStack s, TTree a);
PStack pop_task4(PStack s, TTree *a);
char *parentDFS(TTree root, char **satellites_names, int nr);
void task4(int nr, FILE *f, FILE *out, TTree root);

//-----------------ELIBERARE MEMORIE-----------------

void freeTree(TTree root );
void freeStack(PStack s);

#endif