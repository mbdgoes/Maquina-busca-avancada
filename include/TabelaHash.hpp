#ifndef TABELAHASH_HPP
#define TABELAHASH_HPP

#include <string>
#include <iostream>

#include "ListaEncadeada.hpp"
#include "Palavra.hpp"
#include "ListaConsulta.hpp"

using namespace std;

//classe que armazena a Tabela Hash
class TabelaHash{
    public:

        TabelaHash(int tamanho);

        ~TabelaHash();

        Palavra* Pesquisa(string chave);

        void Insere(Palavra item, string arquivo);

        void Imprime();

        void calcularWtd(TabelaHash* TabelaVocab, int quantidadeDocumentos);

        void calcularWd();

        ListaConsulta Consultar(string query,TabelaHash* TabelaVocab);
    
    private:
        int MAXTAM;
        static const int PRIME_CONST = 31;
        int Hash(string chave);
        ListaEncadeada* Tabela;
};

#endif