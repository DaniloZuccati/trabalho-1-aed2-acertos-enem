#include "BibliotecaENEM.h"

int main (){
    // Recebimento dos dados
    vector<Aluno> dataSheet;
    FILE *arquivoEntrada;
    ArvoreNode* raiz;
    arquivoEntrada = fopen("DadosTratados.csv", "r");

    cout << "COMECADO RECEBIMENTO/CRIACAO VETOR" << "\n";
    
    for (int i = 0; i < TAMANHOARQUIVO; i++){
        dataSheet.push_back(CarregaDados(arquivoEntrada));
    }    
    fclose(arquivoEntrada);
    cout << "FINALIZADO RECEBIMENTO/CRIACAO VETOR" << "\n";
    // Finalizacao do recebimento dos dados

    raiz = CriaArvore(dataSheet);

    menu(raiz);

    return 0;
}