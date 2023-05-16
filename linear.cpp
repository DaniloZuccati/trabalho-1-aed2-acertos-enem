#include <bits/stdc++.h>
using namespace std;

typedef struct Aluno{
    char sex;
    char estado[3];
    double NOTA_NAT;
    double NOTA_HUM;
    double NOTA_LIN;
    double NOTA_MAT;
    double NOTA_RED;
    double MEDIA;
    int ACERT_NAT;
    int ACERT_HUM;
    int ACERT_LIN;
    int ACERT_MAT;
} Aluno;

typedef struct ArvoreNode{
    int altura;
    vector<Aluno> notas;
    ArvoreNode *left;
    ArvoreNode *right;
} ArvoreNode;

Aluno CriarAluno(FILE *arquivoEntrada);

// Retorna o tempo da operação de busca na fila
double BuscaLinear(Aluno alunoBuscado, vector<Aluno> filaAluno);

// imprime as notas
void ImprimeAluno(Aluno aluno);

//Le a entrada das notas do usuário que serão buscadas e retorna um elemento ALuno com essas notas
Aluno LeNotas();

int main (){

    vector<Aluno> DataSheet;
    FILE *arquivoEntrada;
    arquivoEntrada = fopen("tratado.csv", "r");
    Aluno alunoBuscado;
    double tempo;

    int NumCasos;
    cin >> NumCasos;
    for (int i = 0; i < NumCasos; i++){
        DataSheet.push_back(CriarAluno(arquivoEntrada));
    }
    
    alunoBuscado = LeNotas();
    tempo = BuscaLinear(alunoBuscado, DataSheet);
    printf("O tempo para buscar na Fila foi de %lf segundos\n", tempo);
    
    
    fclose(arquivoEntrada);

    return 0;
}

Aluno LeNotas(){

    Aluno buffer;

    printf("Insira as notas na mesma linha na seguinte ordem (LINGUAGENS) (HUMANAS) (NATUREZAS) (MATEMATICA) (REDACAO)\n\n");

    scanf("%lf %lf %lf %lf %lf", &buffer.NOTA_LIN, &buffer.NOTA_HUM, &buffer.NOTA_NAT, &buffer.NOTA_MAT, &buffer.NOTA_RED);

    // Calcula a media que vai ser usada como chave de busca na arvore;
    buffer.MEDIA = (buffer.NOTA_HUM+buffer.NOTA_NAT+buffer.NOTA_MAT+buffer.NOTA_LIN+buffer.NOTA_RED)/5;

    //Coloca como 0 os acertos do aluno de entrada (Esses valores vão ser achados nos dados da arvore)
    buffer.ACERT_HUM = 0;
    buffer.ACERT_LIN = 0;
    buffer.ACERT_MAT = 0;
    buffer.ACERT_NAT = 0;

    return buffer;
};

double BuscaLinear(Aluno alunoBuscado, vector<Aluno> filaAluno){
    int i;

    double tempo = 0.0;

    int tamanho = filaAluno.size();

    // Marca o momento que começou a busca
    clock_t comeco = clock();

    for(i=0;i<tamanho;i++){
        // compara as notas entradas com as notas obtidas dos dados
        if(alunoBuscado.NOTA_HUM==filaAluno[i].NOTA_HUM&&alunoBuscado.NOTA_MAT==filaAluno[i].NOTA_MAT&&alunoBuscado.NOTA_LIN==filaAluno[i].NOTA_LIN){
            
            ImprimeAluno(filaAluno[i]);
            
            break;
        }
    }
    // Marca o momento que terminou a busca
    clock_t fim = clock();
    //  Divide a diferença pela quantidade de clocks por segundos para achar o tempo de execução
    tempo = (double) (fim - comeco) / CLOCKS_PER_SEC;

    return tempo;

};

void ImprimeAluno(Aluno aluno){

    printf("SEXO: %c ", aluno.sex);

    printf("ESTADO: %s || ", aluno.estado);

    printf("NOTA LINGUAGENS: %.2lf ACERTOS: %d || ", aluno.NOTA_LIN, aluno.ACERT_LIN);

    printf("NOTA HUMANAS: %.2lf ACERTOS: %d || ", aluno.NOTA_HUM, aluno.ACERT_HUM);

    printf("NOTA NATUREZAS: %.2lf ACERTOS: %d || ", aluno.NOTA_NAT, aluno.ACERT_NAT);

    printf("NOTA MATEMATICA: %.2lf ACERTOS: %d || ", aluno.NOTA_MAT, aluno.ACERT_MAT);

    printf("NOTA REDACAO: %.0lf\n", aluno.NOTA_RED);
}


Aluno CriarAluno(FILE *arquivoEntrada){
    
    // Informacoes Base      | Sexo e Estado
    
        char sex;
        fscanf (arquivoEntrada, "%c;", &sex);

        char estado[3];
        fscanf (arquivoEntrada, "%c%c;", &estado[0], &estado[1]);

    // Disciplina Natureza   | Nota e Acertos
    
        double NOTA_NAT;
        fscanf (arquivoEntrada, "%lf%*c", &NOTA_NAT);
        
        int ACERT_NAT;
        fscanf (arquivoEntrada, "%d%*c", &ACERT_NAT);

    // Disciplina Humanas    | Nota e Acertos

        double NOTA_HUM;
        fscanf (arquivoEntrada, "%lf%*c", &NOTA_HUM);

        int ACERT_HUM;
        fscanf (arquivoEntrada, "%d%*c", &ACERT_HUM);

    // Disciplina Linguagens | Nota e Acertos

        double NOTA_LIN;
        fscanf (arquivoEntrada, "%lf%*c", &NOTA_LIN);

        int ACERT_LIN;
        fscanf (arquivoEntrada, "%d%*c", &ACERT_LIN);

    // Disciplina Matematica | Nota e Acertos

        double NOTA_MAT;
        fscanf (arquivoEntrada, "%lf%*c", &NOTA_MAT);

        int ACERT_MAT;
        fscanf (arquivoEntrada, "%d%*c", &ACERT_MAT);

    // Discplina Redacao     | Nota

        double NOTA_RED;
        fscanf (arquivoEntrada, "%lf%*c", &NOTA_RED);
    
    // Media Geral 
        
        double MEDIA;
        fscanf (arquivoEntrada, "%lf%*c%*c%*c", &MEDIA);

    Aluno buffer;
    buffer.sex = sex;
    buffer.estado[0] = estado[0];
    buffer.estado[1] = estado[1];
    buffer.NOTA_NAT = NOTA_NAT;
    buffer.NOTA_HUM = NOTA_HUM;
    buffer.NOTA_LIN = NOTA_LIN;
    buffer.NOTA_MAT = NOTA_MAT;
    buffer.NOTA_RED = NOTA_RED;
    buffer.MEDIA = MEDIA;
    buffer.ACERT_NAT = ACERT_NAT;
    buffer.ACERT_HUM = ACERT_HUM;
    buffer.ACERT_LIN = ACERT_LIN;
    buffer.ACERT_MAT = ACERT_MAT;
            

    return buffer;
}