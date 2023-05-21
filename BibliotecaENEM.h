#ifndef BIBLIOTECAENEM_H

#include <bits/stdc++.h>
#define TAMANHOARQUIVO 2236968
using namespace std;

typedef struct Aluno{
    char sex;
    char estado[3];
    double notaNat;
    double notaHum;
    double notaLin;
    double notaMat;
    double notaRed;
    double media;
    int acertNat;
    int acertHum;
    int acertLin;
    int acertMat;
} Aluno;

typedef struct ArvoreNode{
    int altura;
    double media;
    vector<Aluno> notas;
    ArvoreNode *left;
    ArvoreNode *right;
} ArvoreNode;

Aluno CarregaDados(FILE *arquivoEntrada);

Aluno LeNotas();

ArvoreNode* inserir(ArvoreNode *raiz, Aluno aluno);

ArvoreNode* novoNo(Aluno aluno, double media);

ArvoreNode* rotacaoEsquerda(ArvoreNode *r);

ArvoreNode* rotacaoDireita(ArvoreNode *r);

ArvoreNode* rotacaoEsquerdaDireita(ArvoreNode *r);

ArvoreNode* rotacaoDireitaEsquerda(ArvoreNode *r);

ArvoreNode* balancear(ArvoreNode *raiz);

ArvoreNode* CriaArvore(vector<Aluno> dataSheet);

ArvoreNode* remover(ArvoreNode *raiz, double chave);

double modulo(double n);

int maior(int altura1, int altura2);

int alturaDoNo(ArvoreNode *no);

int fatorDeBalanceamento(ArvoreNode *no);

int igual(double a, double b);

void ImprimeAluno(Aluno aluno);

void buscarNota(ArvoreNode *raiz, Aluno alunoBuscado);

void buscarMedia(ArvoreNode *raiz, double media);

void BuscaLinear(Aluno alunoBuscado, vector<Aluno> filaAluno);

void menu(ArvoreNode *raiz);

void imprimeopcoes();

void ImprimirTodosVetor(vector<Aluno> filaAluno);

#endif