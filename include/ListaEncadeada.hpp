#pragma once

#include <string>
#include "Palavra.hpp"

//Lista que encadeia os elementos que se sobrepuseram com o mesmo Hash na TabelaHash

class Node{
    public:
        Node();
    private:
        Palavra item;
        Node *prox;
    
    friend class ListaEncadeada;
};


class ListaEncadeada{
    public:
        ListaEncadeada();


        void InsereFinal(Palavra item);

        Palavra* Pesquisa(string chave);

        void aumentarFrequencia(string chave);

        void Imprime();

        void calcularWtd(TabelaHash* TabelaVocab, int quantidadeDocumentos);

        void calcularWd();

    private:
        Node* primeiro;
        Node* ultimo;
        int tamanho;

    friend class TabelaHash;
};
