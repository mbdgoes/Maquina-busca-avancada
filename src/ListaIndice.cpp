#include <iostream>
#include <string>
#include <cmath>
#include "TabelaHash.hpp"

using namespace std;



NodeIndice::NodeIndice(){
    arquivo = " ";
    frequencia = 0;
    Wtd = 0;
    prox = nullptr;
}

ListaIndice::ListaIndice(){
    primeiro = new NodeIndice();
    ultimo = primeiro;
    tamanho = 0;
}

void ListaIndice::InsereFinal(string arquivo, int frequencia){
    NodeIndice* aux;
    aux = new NodeIndice();

    if(tamanho == 0){
        aux->arquivo = arquivo;
        aux->frequencia = frequencia;
        aux->prox = nullptr;
        primeiro = aux;
        ultimo = aux;
        tamanho++;
    }
    else{
        aux->arquivo = arquivo;
        aux->frequencia = frequencia;
        ultimo->prox = aux;
        ultimo = aux;
        tamanho++;
    }
}

int ListaIndice::Pesquisa(string arquivo){
    int num = -1;
    NodeIndice *aux;

    aux = primeiro;

    while(aux!=nullptr){
        if(aux->arquivo == arquivo){
            num = aux->frequencia;
            break;
        }
        aux = aux->prox;
    }

    return num;
}

void ListaIndice::Imprime(){
    NodeIndice *aux;

    aux = primeiro;
    while(aux!=nullptr){
        cout << "(" << aux->arquivo << ", " << aux->frequencia << ", " << aux->Wtd << ", tamanho = " << 
        this->tamanho << ", Wtd: " << aux->Wtd << ")" << endl << endl;
        aux = aux->prox;
    }

}

void ListaIndice::aumentarFrequencia(string arquivo){
    NodeIndice *aux;

    aux = primeiro;

    while(aux!=nullptr){
        if(aux->arquivo == arquivo){
            aux->frequencia++;
            break;
        }
        aux = aux->prox;
    }
}

void ListaIndice::calcularWtd(TabelaHash* TabelaVocab, int quantidadeDocumentos){
    NodeIndice *aux;
    Palavra* palavraAux = new Palavra();

    aux = primeiro;

    //chave = aux->arquivo, o "arquivo" na tabela de vocabulario sao as palavras
    //pesquisa no Hashmap do vocabulario essa chave
    //pega o tamanho  e coloca em tamanho

    while(aux != nullptr){
        string chave = aux->arquivo; //o aux->arquivo eh a palavra presente no documento
        palavraAux = TabelaVocab->Pesquisa(chave); //Palavra na tabela de vocabulario
        int tamanho = palavraAux->indice.tamanho; //quantidade de documentos que possuem a palavra

        if(tamanho > 0){
            aux->Wtd = aux->frequencia * (log(quantidadeDocumentos/tamanho));
        }
        aux = aux->prox;
    }

}

float ListaIndice::getWtd(string word){
    NodeIndice* aux;

    aux = primeiro;

    while(aux != nullptr){
        if(aux->arquivo == word){
            return aux->Wtd;
        }
        aux = aux->prox;
    }

    return 0;

}