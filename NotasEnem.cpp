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

int main (){

    vector<Aluno> DataSheet;
    FILE *arquivoEntrada;
    arquivoEntrada = fopen("tratado.csv", "r");

    int NumCasos;
    cin >> NumCasos;
    for (int i = 0; i < NumCasos; i++){
        DataSheet.push_back(CriarAluno(arquivoEntrada));
    }
    
    fclose(arquivoEntrada);

    return 0;
}

Aluno CriarAluno(FILE *arquivoEntrada){
    
    // Informacoes Base      | Sexo e Estado
    
        char sex;
        fscanf (arquivoEntrada, "%*c%c%*c", &sex);

        char estado[3];
        fscanf (arquivoEntrada, "%c%c%*c", &estado[0], &estado[1]);

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
