#include <bits/stdc++.h>
#define TAMANHOARQUIVO 2236968
using namespace std;

int contador = 0;

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


//NotasEnem.h

Aluno CriarAluno(FILE *arquivoEntrada);

ArvoreNode* inserir(ArvoreNode *raiz, vector<Aluno> dataSheet, int index);

ArvoreNode* novoNo(Aluno aluno, double media);

ArvoreNode* rotacaoEsquerda(ArvoreNode *r);

ArvoreNode* rotacaoDireita(ArvoreNode *r);

ArvoreNode* rotacaoEsquerdaDireita(ArvoreNode *r);

ArvoreNode* rotacaoDireitaEsquerda(ArvoreNode *r);

ArvoreNode* balancear(ArvoreNode *raiz);

int maior(int altura1, int altura2);

int alturaDoNo(ArvoreNode *no);

int fatorDeBalanceamento(ArvoreNode *no);

void ComecaCriarNode (vector<Aluno> dataSheet);

//NotasEnem.h


int main() {

    // Recebimento dos dados
    vector<Aluno> dataSheet;
    FILE *arquivoEntrada;
    arquivoEntrada = fopen("tratado.csv", "r");

    // NAO SABEMOS PQ, MAS NAO MEXA
    fscanf (arquivoEntrada, "%*c%*c");

    for (int i = 0; i < 10001; i++){
        dataSheet.push_back(CriarAluno(arquivoEntrada));
    }    
    fclose(arquivoEntrada);
    // Finalizacao do recebimento dos dados

    ComecaCriarNode(dataSheet);

    return 0;
}

Aluno CriarAluno(FILE *arquivoEntrada){
    
    // Informacoes Base      | Sexo e Estado
    
        char sex;
        fscanf (arquivoEntrada, "%*c%c%*c", &sex);

        char estado[3];
        fscanf (arquivoEntrada, "%c%c%*c", &estado[0], &estado[1]);

    // Disciplina Natureza   | Nota e Acertos
    
        double notaNat;
        fscanf (arquivoEntrada, "%lf%*c", &notaNat);
        
        int acertNat;
        fscanf (arquivoEntrada, "%d%*c", &acertNat);

    // Disciplina Humanas    | Nota e Acertos

        double notaHum;
        fscanf (arquivoEntrada, "%lf%*c", &notaHum);

        int acertHum;
        fscanf (arquivoEntrada, "%d%*c", &acertHum);

    // Disciplina Linguagens | Nota e Acertos

        double notaLin;
        fscanf (arquivoEntrada, "%lf%*c", &notaLin);

        int acertLin;
        fscanf (arquivoEntrada, "%d%*c", &acertLin);

    // Disciplina Matematica | Nota e Acertos

        double notaMat;
        fscanf (arquivoEntrada, "%lf%*c", &notaMat);

        int acertMat;
        fscanf (arquivoEntrada, "%d%*c", &acertMat);

    // Discplina Redacao     | Nota

        double notaRed;
        fscanf (arquivoEntrada, "%lf%*c", &notaRed);
    
    // Media Geral 
        
        double media;
        fscanf (arquivoEntrada, "%lf%*c%*c%*c", &media);

    Aluno buffer;
    buffer.sex = sex;
    buffer.estado[0] = estado[0];
    buffer.estado[1] = estado[1];
    buffer.notaNat = notaNat;
    buffer.notaHum = notaHum;
    buffer.notaLin = notaLin;
    buffer.notaMat = notaMat;
    buffer.notaRed = notaRed;
    buffer.media = media;
    buffer.acertNat = acertNat;
    buffer.acertHum = acertHum;
    buffer.acertLin = acertLin;
    buffer.acertMat = acertMat;

    return buffer;
}

ArvoreNode* novoNo(Aluno aluno, double media){
    ArvoreNode *novo = new ArvoreNode;
    if(novo){
        novo->notas.push_back(aluno);
        novo->media = media;
        novo->altura = 0;
        novo->left = NULL;
        novo->right = NULL;
    }
    else
        printf("\nERRO ao alocar no em novoNo!\n");
    return novo;
}

void ComecaCriarNode (vector<Aluno> dataSheet){
    ArvoreNode *Arvore = NULL;
    for (int i = 0; i < 10000; i++){
        Arvore = inserir(Arvore, dataSheet, i);
    } 
    cout << "Oi";
}

ArvoreNode* inserir(ArvoreNode *raiz, vector<Aluno> dataSheet, int index){
    if(raiz == NULL) // arvore vazia
        return novoNo(dataSheet.at(index), dataSheet.at(index).media);
    else{ // insercao sera a esquerda ou a direita
        if(dataSheet.at(index).media < raiz->media)
            raiz->left = inserir(raiz->left, dataSheet, index);
        else if(dataSheet.at(index).media > raiz->media)
            raiz->right = inserir(raiz->right, dataSheet, index);
        else contador++;
            //printf("\nInsercao nao realizada!\n");
    }

    // Recalcula a altura de todos os nos entre a raiz e o novo no inserido
    raiz->altura = maior(alturaDoNo(raiz->left), alturaDoNo(raiz->right)) + 1;

    // verifica a necessidade de rebalancear a arvore
    raiz = balancear(raiz);

    return raiz;
}

int maior(int altura1, int altura2){
    // Calcula o maior entre duas alturas
    return (altura1 > altura2)? altura1: altura2;
}

int alturaDoNo(ArvoreNode *no){
    // Retorna a altura de um no ou -1 caso ele seja null
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

int fatorDeBalanceamento(ArvoreNode *no){
    // Calcula e retorna o fator de balanceamento de um no
    if(no)
        return (alturaDoNo(no->left) - alturaDoNo(no->right));
    else
        return 0;
}

ArvoreNode* rotacaoEsquerda(ArvoreNode *r){
    ArvoreNode *y, *f;

    y = r->right; // y aponta para a subarvore direita da raiz r
    f = y->left; // f aponta para o filho left de y

    y->left = r; // o filho left de y passa a ser a raiz r
    r->right = f; // o filho right de r passa a ser f

    // recalcula a altura dos nos que foram movimentados
    r->altura = maior(alturaDoNo(r->left), alturaDoNo(r->right)) + 1;
    y->altura = maior(alturaDoNo(y->left), alturaDoNo(y->right)) + 1;

    return y;
}

ArvoreNode* rotacaoDireita(ArvoreNode *r){
    ArvoreNode *y, *f;

    y = r->left;
    f = y->right;

    y->right = r;
    r->left = f;

    r->altura = maior(alturaDoNo(r->left), alturaDoNo(r->right)) + 1;
    y->altura = maior(alturaDoNo(y->left), alturaDoNo(y->right)) + 1;

    return y;
}


ArvoreNode* rotacaoEsquerdaDireita(ArvoreNode *r){
    r->left = rotacaoEsquerda(r->left);
    return rotacaoDireita(r);
}

ArvoreNode* rotacaoDireitaEsquerda(ArvoreNode *r){
    r->right = rotacaoDireita(r->right);
    return rotacaoEsquerda(r);
}

ArvoreNode* balancear(ArvoreNode *raiz){
    short fb = fatorDeBalanceamento(raiz);

    // Rotacao a esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->right) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotacao a direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->left) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotacao dupla a esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->left) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotacao dupla a direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->right) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}