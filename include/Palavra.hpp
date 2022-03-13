#pragma once
#include <string>
#include "ListaConsulta.hpp"

class TabelaHash;

using namespace std;

//Inicializacao da classe palavra e a lista de Indices que cada palavra possui como membro

class NodeIndice{
    public:
        NodeIndice();
    private:
        std::string arquivo;
        int frequencia;
        NodeIndice *prox;
        float Wtd;
    
    friend class ListaIndice;
    friend class Palavra;
};

class ListaIndice{
    public:
        ListaIndice();


        void InsereFinal(string arquivo, int indice);


        int Pesquisa(string arquivo);

        void aumentarFrequencia(string arquivo);

        void Imprime();

        void calcularWtd(TabelaHash* TabelaVocab, int quantidadeDocumentos);

        float getWtd(string word);
        
        int tamanho;

    private:
        NodeIndice* primeiro;
        NodeIndice* ultimo;
    
    friend class Palavra;
};

class Palavra{
    public:
        Palavra();
        void CalcularWd();
        ListaConsulta getDocumentos();

        string chave;
        ListaIndice indice;
        float Wd;

        
};
 