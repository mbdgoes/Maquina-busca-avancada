#include <string>
#include <cmath>
#include "Palavra.hpp"

using namespace std;

Palavra::Palavra(){
    chave = "-1";
    indice = ListaIndice();
    Wd = 0;
}

void Palavra::CalcularWd(){
    NodeIndice* aux = indice.primeiro;
    float soma = 0;

    while(aux != nullptr){
        soma += pow(aux->Wtd,2);
        aux = aux->prox;
    }

    Wd = sqrt(soma);

}


//retorna a lista de documentos que contem dada palavra
ListaConsulta Palavra::getDocumentos(){
    NodeIndice* aux = indice.primeiro;
    ListaConsulta listaDocumentos;

    while(aux != nullptr){
        listaDocumentos.InsereFinal(aux->arquivo,0);
        aux = aux->prox;
    }

    return listaDocumentos;
}