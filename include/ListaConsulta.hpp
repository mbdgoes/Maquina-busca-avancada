#pragma once

#include <string>

using namespace std;

//Node e listas utilizadas para ordenacao e representacao do resultado final

class NodeConsulta{
    public:
        NodeConsulta();
    private:
        string nomeArquivo;
        float resultado;
        NodeConsulta* prox;

    friend class ListaConsulta;
    friend class TabelaHash;
};

class ListaConsulta{
    public:
        ListaConsulta();

        void InsereFinal(string nomeArquivo, float resultado);

        void Imprime();

        void Ordena(NodeConsulta** cabecaRef);

        NodeConsulta* Merge(NodeConsulta* a, NodeConsulta* b);

        void DivideLista(NodeConsulta* source, NodeConsulta** frente, NodeConsulta** final);


        NodeConsulta* Pesquisa(string chave);

        NodeConsulta* primeiro;
    private:
        int tamanho;
        NodeConsulta* ultimo;
    friend class TabelaHash;
};