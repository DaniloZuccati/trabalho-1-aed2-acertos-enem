#include <bits/stdc++.h>
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
