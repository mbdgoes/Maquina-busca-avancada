#include <string>
#include <iostream>
#include "ListaEncadeada.hpp"
#include "Palavra.hpp"

using namespace std;

Node::Node(){
    item.chave = "-1";
    prox = nullptr;
}

ListaEncadeada::ListaEncadeada(){
    primeiro = new Node();
    ultimo = primeiro;
    tamanho = 0;
}

void ListaEncadeada::InsereFinal(Palavra item){
    Node* aux;
    aux = new Node();

    if(tamanho == 0){
        aux->item = item;
        aux->prox = nullptr;
        primeiro = aux;
        ultimo = aux;
        tamanho++;
    }
    else{
        aux->item = item;
        ultimo->prox = aux;
        ultimo = aux;
        tamanho++;
    }
}

//pesquisa na lista encadeada, retorna uma palavra que contem -1 como chave se nao encontrada
Palavra* ListaEncadeada::Pesquisa(string chave){
    Palavra* palavraAux = new Palavra();
    Node *aux;

    aux = primeiro;

    while(aux!=nullptr){
        if(aux->item.chave == chave){
            palavraAux = &(aux->item);
            break;
        }
        aux = aux->prox;
    }

    return palavraAux;
}

//essa impressao era usada para controlar os resultados do programa
void ListaEncadeada::Imprime(){
    Node *aux;

    aux = primeiro;
    while(aux!=nullptr){
        cout << aux->item.chave << ",Wd: "<< aux->item.Wd << endl;
        aux->item.indice.Imprime();
        aux = aux->prox;
    }
}


void ListaEncadeada::calcularWtd(TabelaHash* TabelaVocab, int quantidadeDocumentos){
    Node* aux;

    aux = primeiro;

    while(aux != nullptr){
        aux->item.indice.calcularWtd(TabelaVocab,quantidadeDocumentos);
        aux = aux->prox;
    }

}

void ListaEncadeada::calcularWd(){
    Node* aux;
    aux = primeiro;

    while(aux != nullptr){
        aux->item.CalcularWd();
        aux = aux->prox;
    }
}