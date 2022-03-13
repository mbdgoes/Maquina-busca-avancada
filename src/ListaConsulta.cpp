#include "ListaConsulta.hpp"
#include <string>
#include <iostream>

using namespace std;

NodeConsulta::NodeConsulta(){
    nomeArquivo = " ";
    resultado = 0;
    prox = nullptr;
}

ListaConsulta::ListaConsulta(){
    primeiro = new NodeConsulta();
    ultimo = primeiro;
    tamanho = 0;
}


void ListaConsulta::InsereFinal(string nomeArquivo, float resultado){
    NodeConsulta* aux;
    aux = new NodeConsulta();

    if(tamanho == 0){
        aux->nomeArquivo = nomeArquivo;
        aux->resultado = resultado;
        aux->prox = nullptr;
        primeiro = aux;
        ultimo = aux;
        tamanho++;
    }
    else{
        aux->nomeArquivo = nomeArquivo;
        aux->resultado = resultado;
        ultimo->prox = aux;
        ultimo = aux;
        tamanho++;
    }
}

NodeConsulta* ListaConsulta::Pesquisa(string chave){
    NodeConsulta* aux;
    NodeConsulta* nodeNulo;
    nodeNulo = new NodeConsulta();

    aux = primeiro;

    while(aux != nullptr){
        if(aux->nomeArquivo == chave){
            return aux;
        }
        aux = aux->prox;
    }

    return nodeNulo;

}

//Imprime os elementos da lista que vao gerar o resultado final no output
void ListaConsulta::Imprime(){
    NodeConsulta* aux;
    aux = primeiro;
    string idArquivo;
    int count = 0;

    while(aux != nullptr){
        //imprimir apenas os 10 primeiros
        if(count == 10) break;

        //retirar o .txt do final dos arquivos
        idArquivo = aux->nomeArquivo;
        size_t pos = idArquivo.find(".txt");
        if(pos != string::npos) idArquivo.erase(pos, 4);

        cout << idArquivo << " ";
        count++;
        aux = aux->prox;
    }

}

//funcao Merge para auxiliar no MergeSort
NodeConsulta* ListaConsulta::Merge(NodeConsulta* a, NodeConsulta* b){
    NodeConsulta* resultado;

    if(a == nullptr) return b;
    else if(b == nullptr) return a;

    if(a->resultado > b->resultado || (a->resultado == b->resultado && a->nomeArquivo <= b->nomeArquivo)){
        resultado = a;
        resultado->prox = Merge(a->prox,b);
    }
    else{
        resultado = b;
        resultado->prox = Merge(a,b->prox);
    }

    return resultado;

}

//Divisao da lista para ordenacao
void ListaConsulta::DivideLista(NodeConsulta* source, NodeConsulta** frente, NodeConsulta** final){
    NodeConsulta* ptr1;
    NodeConsulta* ptr2;
    ptr2 = source;
    ptr1 = source->prox;

    while(ptr1 != nullptr){
        ptr1 = ptr1->prox;
        if(ptr1 != nullptr){
            ptr2 = ptr2->prox;
            ptr1 = ptr1->prox;
        }
    }

    *frente = source;
    *final = ptr2->prox;
    ptr2->prox = nullptr;

}

//chamada da funcao de mergesort, pacando o elemento cabeca da lista a ser ordenada
void ListaConsulta::Ordena(NodeConsulta** cabecaRef){
    
    NodeConsulta* cabeca = *cabecaRef;
    NodeConsulta* a;
    NodeConsulta* b;

    if((cabeca == nullptr) || (cabeca->prox == nullptr)) return;

    DivideLista(cabeca, &a, &b);

    Ordena(&a);
    Ordena(&b);

    *cabecaRef = Merge(a,b);

}
