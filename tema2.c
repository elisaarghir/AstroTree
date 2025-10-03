/*ARGHIR Elisa-Elena*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

int main(int argc, char **argv) 
{
    if (argc < 4) {
        exit(1);
    }
    char line[256];
    int i;
    FILE *f = fopen(argv[2], "r"); 
    FILE *out = fopen(argv[3], "w");
    int nr_satellites, nr_encodings;
    fgets(line, sizeof(line), f);
    nr_satellites = atoi(line);

    //construiesc un vector de sateliti in care retin numele si frecventa lor
    Satellite *satellites_list = malloc(sizeof(struct Satellite) * nr_satellites);
    for (i = 0; i < nr_satellites; i++) {
        fgets(line, sizeof(line), f);
        int fr;
        char name_buffer[1000];
        sscanf(line, "%d %s", &fr, name_buffer);
        satellites_list[i].fr = fr;
        satellites_list[i].name = malloc((strlen(name_buffer) + 1) * sizeof(char)); 
        strcpy(satellites_list[i].name, name_buffer);
    }

    /*construiesc heap-ul, adaugand cate un TreeNode cu informatiile
    despre fiecare satelit*/
    APrQueue q = malloc(sizeof(PrQueue));
    PQInit(q, nr_satellites);
    for (i = 0; i < nr_satellites; i++) {
        TreeNode *node = malloc(sizeof(TreeNode));
        node->elem.fr = satellites_list[i].fr;
        node->elem.name = malloc(strlen(satellites_list[i].name) + 1);
        strcpy(node->elem.name, satellites_list[i].name);
        node->lt = node->rt = NULL;
        Insert(q, node);
    }

    //construiesc arborele propriu-zis 
    while (q->size > 1) {
        //extrag nodurile cu cea mai mica frecventa din heap, adica
        //cu prioritatea cea mai mare
        TTree s1 = ExtractMin(q);
        TTree s2 = ExtractMin(q);

        //construiesc satelitul s3 de legatura, dupa regulile din cerinta,
        //acesta fiind parintele lui s1 si s2 
        Satellite s3;
        s3.name = malloc(strlen(s1->elem.name) + strlen(s2->elem.name) + 1);
        s3.fr = s1->elem.fr + s2->elem.fr;
        strcpy(s3.name, s1->elem.name);
        strcat(s3.name, s2->elem.name);

        /*creez nodul parinte care ii are ca si copii pe s1 si s2
        si il reintroduc in heap*/
        TTree parent = buildNod(s3, s1, s2);
        free(s3.name);
        Insert(q, parent);
    }

    /*root-ul este ultimul nod din minHeap, dupa ce le-am legat pe 
    toate celelalte dupa criteriile din cerinta*/
    TTree root = ExtractMin(q);

    //aici am impartit functiile conform numarului cerintei
    if (strcmp(argv[1], "-c1") == 0) {
        printBFS(root, out);
    }

    if (strcmp(argv[1], "-c2") == 0) {
        fgets(line, sizeof(line), f);
        nr_encodings = atoi(line);
        task2(nr_encodings, f, out, root);
    }

    if (strcmp(argv[1], "-c3") == 0) {
        fgets(line, sizeof(line), f);
        nr_encodings = atoi(line);
        task3(nr_encodings, f, out, root);
    }

    if (strcmp(argv[1], "-c4") == 0) {
        fgets(line,sizeof(line), f);
        nr_encodings = atoi(line);
        task4(nr_encodings, f, out, root);
    }
    
    fclose(f);
    fclose(out);
    for (i = 0; i < nr_satellites; i++) {
        free(satellites_list[i].name);
    }
    free(satellites_list);
    freeTree(root);
    free(q->elem);
    free(q);
    return 0;
}