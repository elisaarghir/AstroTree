/*ARGHIR Elisa-Elena*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "biblioteca.h"


//-----------------CERINTA 1-----------------

//initializez coada q de prioritati 
//implementarea heap-ului incepe de la
//index 1, de aceea maxSize+1
void PQInit(APrQueue q, int maxSize)
{
    q->size = 0;
    q->maxHeapSize = maxSize + 1;
    q->elem = (TreeNode**)malloc(q->maxHeapSize * sizeof(TreeNode*));
}

/*functie pentru inserarea unui nod in heap, in care actualizez 
nr curent de elemente si repozitionez nodul cu SiftUp, pentru ca trebuie
sa pastrez prioritatea*/
void Insert(APrQueue q, TreeNode *node) 
{
    if (q->size == q->maxHeapSize) {
        exit(1);
    }
    ++(q->size);
    q->elem[q->size] = node;
    SiftUp(q, q->size);
}

//functie pentru repozitionarea unui nod in heap
//compar nodul curent cu parintele sau, aflat la pozitia k/2
//ok se face 1 atunci cand copilul are frecventa mai mica sau nume 
//lexicografic mai mic, si avanseaza in heap, prin interschimbare.
void SiftUp(APrQueue q, int k)
{
    while (k > 1) {
        TreeNode *cd = q->elem[k]; //copil
        TreeNode *pt = q->elem[k / 2]; //parinte
        int ok = 0;
        if (cd->elem.fr < pt->elem.fr) {
            ok = 1;
        }
        else if (cd->elem.fr == pt->elem.fr) {
            if (strcmp(cd->elem.name, pt->elem.name) < 0) {
                ok = 1;
            }
        }
     //daca ok ramane 0 nu e nevoie de interschimbare 
        if (ok == 0) {
            break;
        }
        TreeNode *t =  q->elem[k];
        q->elem[k] = q->elem[k / 2];
        q->elem[k / 2] = t;
        k = k / 2;
    }
}

//functie pe care o folosesc pentru a scoate nodul cu cea mai mare 
//prioritate din heap, adica cel din varf, care are frecventa cea mai mica.
//Dupa ce inlocuiesc radacina cu ultimul nod, pentru a pastra continuitatea,
//verific daca e pus la pozitia corecta cu SiftDown.
TTree ExtractMin(APrQueue q) 
{
    if (q->size == 0) {
        return NULL;
    }
    TTree min = q->elem[1];
    q->elem[1] = q->elem[q->size];
    q->size--;
    if (q->size > 0) {
        SiftDown(q, 1);
    }
    return min;
}

//functie pentru a verifica daca noul nod din radacina e pozitionat corect,
//prin comparatie cu copiii sai
//iau copilul din stanga cu j, dupa care il compar cu cel din dreapta (j + 1)
//si selectez dupa criteriile din cerinta. Apoi compar parintele cu copilul si,
//daca e nevoie, le interschimb
void SiftDown(APrQueue q, int k) 
{
    int j;
    TreeNode *t;
    while (2 * k <= q->size) {
        j = 2 * k; //copilul din stanga 
        int ok = 0;
        //verific daca exista copilul din dreapta si, daca are frecventa mai mica,
        //il selectez pe acesta 
        if (j + 1 <= q->size) { 
            TreeNode *lt = q->elem[j];
            TreeNode *rt = q->elem[j + 1];
            if (rt->elem.fr < lt->elem.fr) {
                ok = 1;
            }
            else if (rt->elem.fr == lt->elem.fr) {
                if (strcmp(rt->elem.name, lt->elem.name) < 0) {
                    ok = 1;
                }
            }
        }
        //aleg copilul din dreapta
        if(ok == 1) 
            j++; 
        //interschimb copilul cu parintele, daca copilul are prioritate mai mare
        //dupa comparatia celor doi 
        ok = 0;
        TreeNode *p = q->elem[k];
        TreeNode *c = q->elem[j];
        if (p->elem.fr > c->elem.fr) {
            ok = 1;
        }
        else if (p->elem.fr == c->elem.fr) {
            if (strcmp(c->elem.name, p->elem.name) < 0) {
                ok = 1;
            }
        }
        if (ok == 0) {
            break;
        }
        t = q->elem[k];
        q->elem[k] = q->elem[j];
        q->elem[j] = t;
        k = j;
    }
}

//functie pentru a crea un nod parinte intr-un arbore, care ma ajuta la
//construirea arborelui
TTree buildNod(Satellite a, TTree ltree, TTree rtree) 
{
    TTree t = malloc(sizeof(TreeNode));
    t->elem.fr = a.fr;
    t->elem.name = malloc((strlen(a.name) + 1) * sizeof(char));
    strcpy(t->elem.name, a.name);
    t->lt = ltree;
    t->rt = rtree;
    return t;
}

//PQueue este coada folosita pentru afisarea BFS a arborelui, 
//care contine doar nodurile de pe un anumit nivel din acesta

AQueue initQueue() {
    AQueue q = malloc(sizeof(struct Queue));
    if (q == NULL) {
        printf("Memorie insuficienta\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    return q;
}

int isEmptyQueue(AQueue q) {
    return q->front == NULL;
}

//functie pentru a adauga un nod din arbore in coada 
void enqueue(AQueue p, TTree a) 
{
    PQueue q;
    if (a == NULL) {
        return;
    }
    q = malloc(sizeof(struct cell));
    if (q == NULL) {
        printf("memorie insuficienta\n");
        return;
    } 
    q->elem = a;
    q->next = NULL;
    //daca coada era goala, front si rear reprezinta chiar prima celula 
    if (isEmptyQueue(p)) {
        p->front = p->rear = q;
        return;
    }
    //leg celula noua la sfarsit 
    p->rear->next = q;
    p->rear = q;
}

//functie pentru a scoate un element (nod al unui arbore) din coada 
TTree dequeue(AQueue p)
{
    PQueue q = p->front;
    TTree t;
    if (isEmptyQueue(p)) {
        printf("coada vida\n");
        return NULL;
    }
    t = p->front->elem;
    //daca coada are un singur element, setez front si rear la NULL,
    //daca nu, actualizez front la urmatorul element 
    if (p->front == p->rear) {
        p->front = p->rear = NULL;
    } else {
        p->front = p->front->next;
    }
    free(q);
    return t;
}

//functie pentru afisarea pe nivel a arborelui, conform cerintei
void printBFS(TTree tree, FILE *f) 
{
    int level, i;
    if (tree == NULL) {
        fprintf(f, "Empty Tree\n");
        return;
    }
    //creez o coada in care adaug elementele si adaug initial radacina arborelui
    AQueue p = initQueue();
    enqueue(p, tree);
    while (!isEmptyQueue(p)) {
        level = 0;
        PQueue t = p->front;
        //numar elementele de pe acel nivel 
        while (t != NULL) {
            level++;
            t = t->next;
        }
        //afisez toate elementele de pe nivelul respectiv 
        for (i = 0; i < level; i++) {
            TTree node = dequeue(p);
            fprintf(f, "%d-%s", node->elem.fr, node->elem.name);
            if (i < level - 1) {
                fprintf(f, " ");
            }
            //adaug in coada copiii, adica nodurile de pe nivelul urmator, 
            //daca exista
            if (node->lt != NULL) {
                enqueue(p, node->lt);
            }
            if (node->rt != NULL) {
                enqueue(p, node->rt);
            }
        }
        fprintf(f, "\n"); 
    }
    free(p);
}

//-----------------CERINTA 2-----------------

//functia task2 se apeleaza doar daca argv[1] este c2
//nr reprezinta numarul de linii cu 0 si 1 pe care le citesc
//dupa ce citesc prima linie, parcurg element cu element si daca e 0 sau 1,
//avansez pe copilul din stanga sau pe copilul din dreapta, conform cerintei

//daca ambii copii sunt nuli, inseamna ca nodul este frunza si am ajuns la final, 
//unde afisez numele satelitului si ma intorc la radacina pentru a relua 
//parcurgerea

void task2(int nr, FILE *f, FILE *out, TTree root) 
{
    char line[1001];
    int i, j;
    for (i = 0; i < nr; i++) {
        fgets(line, sizeof(line), f);
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        TTree node = root;
        int length = strlen(line);
        for (j = 0; j < length; j++) {
            if (line[j] == '0') {
                if (node != NULL) {
                    node = node->lt;
                }
            } else if (line[j] == '1') {
                if (node != NULL) {
                    node = node->rt;
                }
            }
            if (node->lt == NULL && node->rt == NULL) {
                fprintf(out, "%s ", node->elem.name);
                node = root;
            }
        }
        fprintf(out, "\n");
    }
}


//-----------------CERINTA 3-----------------

//pentru aceasta cerinta parcurg arborele DFS si retin calea parcursa
//pana la nodul respectiv in path. Pentru DFS am nevoie de o stiva pentru care 
//am implementat functiile specifice acesteia
PStack initStack() 
{
    PStack s;
    return s = NULL;
}

int isEmptyStack(PStack s) 
{
    return s == NULL;
}

//functie pentru a adauga un nou nod in stiva
PStack push(PStack s, TTree a, char *path) 
{
    PStack t;
    t = (PStack) malloc(sizeof(Stack));
    if (t == NULL) {
        return NULL;
    }
    t->elem = a;
    //retin calea pentru fiecare nod, de la radacina pana la el
    strcpy(t->path, path);
    t->next = s;
    return t;
}

//functie pentru a scoate din stiva un nod 
PStack pop(PStack s, TTree *a, char *path) 
{
    PStack t;
    if (s == NULL) {
        printf("stiva vida\n");
        return NULL;
    }
    *a = s->elem; //salvez nodul curent
    strcpy(path, s->path); //salvez calea parcursa pana la nodul curent
    t = s;
    s = s->next;
    free(t);
    return s;
}

//cu aceasta functie caut numele fiecarui satelit in adancimea arborelui si 
//retin calea in binar de la radacina pana la acesta.
void browseDFS(TTree root, char *name, char *encoding) 
{
    PStack s = NULL;
    TTree current;
    //in path retin codificarea in binar
    char path[1001], copy_path[1001];  
    //calea de la root este vida, deoarece nu are niciun nod anteror
    s = push(s, root, ""); 
    while (s != NULL) {
        s = pop(s, &current, path);
        //verific daca am gasit numele satelitului cautat, adaug in encoding calea 
        //si ies din functie pentru ca l-am gasit
        if (strcmp(current->elem.name, name) == 0) {
                strcpy(encoding, path);
                freeStack(s);
                return;
        }
        //daca are copii, continui si caut in adancime si construiesc codificarea
        //preiau mai intai copilul din dreapta pentru ca cel din stanga sa fie
        //primul scos din stiva 
        if (current->rt != NULL) { 
            strcpy(copy_path, path);
            strcat(copy_path, "1");
            s = push(s, current->rt, copy_path);
        }
        if (current->lt != NULL) {
            strcpy(copy_path, path);
            strcat(copy_path, "0");
            s = push(s, current->lt, copy_path);
        }
    }
    //daca nu am gasit numele satelitului, codificarea va fi goala.
    encoding[0] = '\0';
    freeStack(s);
}

//functia task3 se apeleaza doar daca argv[1] este c3
//citesc nr sateliti pe care ii caut pe rand, in adancime, in arbore
//encoding imi retine codificarea pe biti, daca satelitul a fost gasit
//daca nu a fost gasit, encoding va fi gol
void task3(int nr, FILE *f, FILE *out, TTree root) 
{
    char name[256], encoding[1001];
    int i;
    for (i = 0; i < nr; i++) {
        fgets(name, sizeof(name), f); 
        if (name[strlen(name) - 1] == '\n') {
            name[strlen(name) - 1] = '\0';
        }
        //caut satelitul in adancime si retin calea de la radacina
        browseDFS(root, name, encoding);
        if (encoding[0] == '\0') {
            fprintf(out, "Not Found\n");
        } else {
            fprintf(out, "%s", encoding);
        }
    }
    fprintf(out, "\n");
}

//-----------------CERINTA 4-----------------

//pentru aceasta cerinta am ales tot o parcurgere DFS a arborelui, in
//care, la fiecare nod curent la care ma aflu, caut sa vad daca numele
//satelitilor din input se regaseste in numele acestuia si inaintez 
//in adancime daca mai exista posibilitatea

//am adaptat functiile push si pop de mai devreme, dar de data aceasta fara 
//path, deoarece nu mai am nevoie se acest camp
PStack push_task4(PStack s, TTree a) 
{
    PStack t;
    t = (PStack) malloc(sizeof(Stack));
    if (t == NULL) {
        return NULL;
    }
    t->elem = a;
    t->next = s;
    return t;
}

PStack pop_task4(PStack s, TTree *a) {
    PStack t;
    if (s == NULL) {
        printf("stiva vida\n");
        return NULL;
    }
    *a = s->elem;
    t = s;
    s = s->next;
    free(t);
    return s;
}

// Aceasta este functia principala pe care o folosesc pentru rezolvare,
// in care parcurg arborele in adancime, extragand din stiva cate un nod,
// pe rand. La fiecare nod extras verific daca fiecare nume din sattelites_names,
// vector care imi retine numele satelitilor din inputul cerintei 4, se regaseste
// in numele nodului curent. Daca da, acutalizez parent si merg si mai mult in
// adancime, daca e cazul.
char *parentDFS(TTree root, char **satellites_names, int nr) 
{
    PStack s = NULL;
    TTree current;
    int found_names, i;
    char *parent = NULL;
    s = push_task4(s, root); 
    while (s != NULL) {
        s = pop_task4(s, &current);
        found_names = 0;
        //parcurg vectorul cu numele satelitilor si daca numele lor se regaseste
        //in numele nodului curent, incrementez variabila found_names
        for (i = 0; i < nr; i++) {
            if (strstr(current->elem.name, satellites_names[i]) != NULL) {
                found_names++;
            }
        }
        if (found_names == nr) {
            parent = current->elem.name;
        }
        //merg mai mult in adancimea arborelui daca mai am posibilitatea 
        if (current->rt != NULL) {
            s = push_task4(s, current->rt);
        }
        if (current->lt != NULL) {
            s = push_task4(s, current->lt);
        }
    }
    return parent;
}

//retin in satellites_names numele tuturor satelitior din input
//din cadrul cerintei 4, iar in parent, parintele comun al acestora,
//daca exista. Dupa ce am construit vectorul de sateliti apelez 
//functia parentDFS care imi cauta parintele in adancimea arborelui.
void task4(int nr, FILE *f, FILE *out, TTree root) 
{
    char name[256], **satellites_names, *parent;
    int i; 
    satellites_names = malloc(nr * sizeof(char *));
    for (i = 0; i < nr; i++) {
        fgets(name, sizeof(name), f);
        if (name[strlen(name) - 1] == '\n') {
            name[strlen(name) - 1] = '\0';
        }
        satellites_names[i] = malloc(strlen(name) + 1);
        if (satellites_names[i] == NULL) {
            return;
        }
        strcpy(satellites_names[i], name);
    }
    parent = parentDFS(root, satellites_names, nr);
    if (parent != NULL) {
        fprintf(out, "%s\n", parent);
    } else {
        fprintf(out, "Not Found\n");
    }
    for (i = 0; i < nr; i++) {
        free(satellites_names[i]);
    }
    free(satellites_names);
}

//-----------------ELIBERARE MEMORIE-----------------

void freeTree(TTree root) 
{
    if (root == NULL) {
        return;
    }
    freeTree(root->lt);
    freeTree(root->rt);
    free(root->elem.name);
    free(root);
}

void freeStack(PStack s) 
{
    PStack t;
    while (s != NULL) {
        t = s;
        s = s->next;
        free(t);
    }
}