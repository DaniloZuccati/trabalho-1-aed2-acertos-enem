#include "BibliotecaENEM.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
const bool IS_WINDOWS = true;
#else
const bool IS_WINDOWS = false;
#endif

short VERIFICADOR = 0;

int contador = 0;  // conta a quantidade de medias unicas (nos) da arvore 

Aluno CarregaDados(FILE *arquivoEntrada){

    vector<Aluno> dataSheet;
    
    // Informacoes Base      | Sexo e Estado
    
        char sex, estado[3];
        fscanf (arquivoEntrada, "%*c%c;%c%c%*c", &sex,&estado[0], &estado[1]);
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
        fscanf (arquivoEntrada, "%lf;%*c", &media);
        if (!IS_WINDOWS) fscanf(arquivoEntrada, "%*c");

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
    contador++;
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

ArvoreNode* CriaArvore(vector<Aluno> dataSheet){
    ArvoreNode* Arvore = NULL;

    //marca o momento de inicio de criação da arvore
    clock_t inicio = clock();
    printf("Comecou a arvore\n");

    for (int i = 0; i < TAMANHOARQUIVO; i++){
        Arvore = inserir(Arvore, dataSheet.at(i));
    }

    //marca o momento do final da criação da arvore
    clock_t fim = clock();
    printf("Terminou em %lf segundos\n", (double)(fim-inicio)/CLOCKS_PER_SEC);

    //informações basicas da arvore
    printf("Arvore com %d nos e %d de altura\n", contador, Arvore->altura);

    return Arvore;
}

ArvoreNode* inserir(ArvoreNode *raiz, Aluno aluno){
    if(raiz == NULL) // arvore vazia
        return novoNo(aluno, aluno.media);
    else{ // insercao sera a esquerda ou a direita
        if(aluno.media < raiz->media)
            raiz->left = inserir(raiz->left, aluno);
        else if(aluno.media > raiz->media)
            raiz->right = inserir(raiz->right, aluno);
        else if(aluno.media == raiz->media){
            raiz->notas.push_back(aluno);
        }
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

void buscarNota(ArvoreNode *raiz, Aluno alunoBuscado){
    if(raiz){
        if(igual(alunoBuscado.media, raiz->media)) {
            if (raiz->notas.size() > 1) BuscaLinear(alunoBuscado, raiz->notas);
            else ImprimeAluno(raiz->notas.at(0));
            VERIFICADOR++;
        }
        else if(alunoBuscado.media < raiz->media) buscarNota(raiz->left, alunoBuscado);
        else buscarNota(raiz->right, alunoBuscado);
    }
}

void buscarMedia(ArvoreNode *raiz, double media){
    if(raiz){
        if(igual(media,raiz->media)) {
            ImprimirTodosVetor(raiz->notas);
            VERIFICADOR++;
        }
        else if(media < raiz->media) buscarMedia(raiz->left, media);
        else buscarMedia(raiz->right, media);    
    }
};

void ImprimeAluno(Aluno aluno){
    
    printf("|| SEXO: %c\n", aluno.sex);

    printf("|| ESTADO: %c%c\n", aluno.estado[0], aluno.estado[1]);

    printf("|| NOTA LINGUAGENS: %.2lf ACERTOS: %d\n", aluno.notaLin, aluno.acertLin);

    printf("|| NOTA HUMANAS: %.2lf ACERTOS: %d\n", aluno.notaHum, aluno.acertHum);

    printf("|| NOTA NATUREZAS: %.2lf ACERTOS: %d\n", aluno.notaNat, aluno.acertNat);

    printf("|| NOTA MATEMATICA: %.2lf ACERTOS: %d\n", aluno.notaMat, aluno.acertMat);

    printf("|| NOTA REDACAO: %.0lf\n", aluno.notaRed);

    printf("|| MEDIA : %.2lf\n\n", aluno.media);
}

void BuscaLinear(Aluno alunoBuscado, vector<Aluno> filaAluno){

    int tamanho = filaAluno.size();

    for(int i=0;i<tamanho;i++){
        // compara as notas entradas com as notas obtidas dos dados
        if(igual(alunoBuscado.notaHum,filaAluno[i].notaHum) &&
           igual(alunoBuscado.notaMat,filaAluno[i].notaMat) &&
           igual(alunoBuscado.notaLin,filaAluno[i].notaLin) &&
           igual(alunoBuscado.notaNat,filaAluno[i].notaNat) &&
           igual(alunoBuscado.notaRed,filaAluno[i].notaRed)){ 
            ImprimeAluno(filaAluno[i]); 
            break;
        }
    }
}

void ImprimirTodosVetor(vector<Aluno> filaAluno){
    for (unsigned int i = 0; i < filaAluno.size(); i++){
        printf ("Aluno %d: \n", i+1);
        ImprimeAluno(filaAluno[i]);
    }
}

Aluno LeNotas(){

    Aluno buffer;

    printf("Insira as notas na mesma linha na seguinte ordem (LINGUAGENS) (HUMANAS) (NATUREZAS) (MATEMATICA) (REDACAO)\n\n");

    scanf("%lf %lf %lf %lf %lf", &buffer.notaLin, &buffer.notaHum, &buffer.notaNat, &buffer.notaMat, &buffer.notaRed);

    // Calcula a media que vai ser usada como chave de busca na arvore;
    buffer.media = (buffer.notaHum+buffer.notaNat+buffer.notaMat+buffer.notaLin+buffer.notaRed)/5;

    //Coloca como 0 os acertos do aluno de entrada (Esses valores vão ser achados nos dados da arvore)
    buffer.acertHum = 0;
    buffer.acertLin = 0;
    buffer.acertMat = 0;
    buffer.acertNat = 0;

    return buffer;
};

double modulo(double n){
    if(n<0)return -n;
    return n;
};

int igual(double a, double b){
    if(modulo(a-b)<=0.001)return 1;
    return 0;
};

void menu(ArvoreNode *raiz){
    int resposta = 1;
    double media;

    while(resposta){
        VERIFICADOR = 0;
        imprimeopcoes();

        scanf("%d", &resposta);

        switch (resposta)
        {
        case 1:
            buscarNota(raiz, LeNotas());
            if (!VERIFICADOR) printf ("NOTA NAO ENCONTRADA\n"); 

            break;

        case 2:
            printf("Insira a media\n");

            scanf("%lf", &media);
            
            buscarMedia(raiz, media);
            if (!VERIFICADOR) printf ("MEDIA NAO ENCONTRADA\n");

            break;

        case 3:
            VERIFICADOR++;
            printf("Insira a media\n");

            scanf("%lf", &media);

            remover(raiz, media);
            if (VERIFICADOR){
                printf ("REMOVIDO COM SUCESSO\n");
                printf ("ALTURA DA ARVORE: %d\n", raiz->altura);
            }

            break;

        case 0:
            break;

        default:
            printf("\nOpcao nao encontrada\n");

            break;
        }        
    }
};

void imprimeopcoes(){
    printf("Insira o numero da funcao desejada\n\n");
    printf("1 - buscar uma nota em especifico\n");
    printf("2 - buscar todas as notas com uma mesma media\n");
    printf("3 - excluir todas as notas com uma mesma media\n");
    printf("0 - encerrar o programa\n\n");
};

/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
ArvoreNode* remover(ArvoreNode *raiz, double chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n\n");
        VERIFICADOR--;
        return NULL;
    } else { // procura o nó a remover
        if(igual(raiz->media, chave)) {
            // remove nós folhas (nós sem filhos)
            if(raiz->left == NULL && raiz->right == NULL) {
                delete raiz;
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->left != NULL && raiz->right != NULL){
                    ArvoreNode *aux = raiz->left;
                    while(aux->right != NULL)
                        aux = aux->right;
                    raiz->media = aux->media;
                    raiz->notas = aux->notas;
                    aux->media = chave;
                    //printf("Elemento trocado: %d !\n", chave);
                    raiz->left = remover(raiz->left, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    ArvoreNode *aux;
                    if(raiz->left != NULL)
                        aux = raiz->left;
                    else
                        aux = raiz->right;
                    delete raiz;
                    //printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->media)
                raiz->left = remover(raiz->left, chave);
            else
                raiz->right = remover(raiz->right, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaDoNo(raiz->left), alturaDoNo(raiz->right)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}