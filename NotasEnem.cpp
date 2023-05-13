#include <bits/stdc++.h>
using namespace std;

typedef struct Aluno{
    char sex[2];
    char estado[3];
    double *NOTA_MAT;
    double *NOTA_NAT;
    double *NOTA_HUM;
    double *NOTA_LIN;
    double *NOTA_RED;
    double *MEDIA;
} Aluno;

typedef struct ArvoreNode{
    int altura;
    Aluno *notas;
    ArvoreNode *left;
    ArvoreNode *right;
} ArvoreNode;

int main (){

    

    return 0;
}