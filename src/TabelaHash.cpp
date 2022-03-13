#include <string>
#include <cmath>
#include <sstream>

#include "TabelaHash.hpp"

using namespace std;

TabelaHash::TabelaHash(int tamanho){
    MAXTAM = tamanho;
    Tabela = new ListaEncadeada[MAXTAM];
}

TabelaHash::~TabelaHash(){
    delete[] Tabela;
}

//pesquisa retorna -1 se nao for encontrado-> palavra vazia inicializada com -1
Palavra* TabelaHash::Pesquisa(string chave){
    int pos;
    Palavra* aux = new Palavra();


    pos = Hash(chave);
    aux = Tabela[pos].Pesquisa(chave);

    return aux;
}


void TabelaHash::Insere(Palavra item, string arquivo){
    Palavra* aux;
    int pos;

    aux = Pesquisa(item.chave);

    //se ja existe chave na tabela
    if(aux->chave != "-1"){
        //se o indice ja existe
        if(aux->indice.Pesquisa(arquivo) != -1){
            aux->indice.aumentarFrequencia(arquivo);
        }
        else{
            //insercao do indice no final da palavra
            aux->indice.InsereFinal(arquivo,1);
        }
    }
    else{
        //insercao do elemento na tabela
        pos = Hash(item.chave);
        item.indice.InsereFinal(arquivo,1);
        Tabela[pos].InsereFinal(item);
    }

}

int TabelaHash::Hash(string chave){
    size_t sum;

    //funcao de Hashing, realizada para minimizar colisoes
    for(unsigned int i = 0;i < chave.length();i++){
        sum += (chave[i] * (int)pow(PRIME_CONST,i)) % MAXTAM;
    }
    return sum % MAXTAM;
}


void TabelaHash::Imprime(){
    for(int i = 0; i < MAXTAM;i++){
        cout << i << endl;
        Tabela[i].Imprime();
        cout << endl;
    }
}

void TabelaHash::calcularWtd(TabelaHash* TabelaVocab, int quantidadeDocumentos){

    for(int i = 0; i<MAXTAM;i++){
        Tabela[i].calcularWtd(TabelaVocab, quantidadeDocumentos);
    }
}

void TabelaHash::calcularWd(){
    for(int i = 0; i<MAXTAM;i++){
        Tabela[i].calcularWd();
    }
}

ListaConsulta TabelaHash::Consultar(string query, TabelaHash* TabelaVocab){
    istringstream ss(query);
    string word;
    string chave;

    Palavra* palavraAux = new Palavra();
    Palavra* documento = new Palavra();

    ListaConsulta listaDocumentos;
    ListaConsulta listaResultados;
    NodeConsulta* aux;


    while(ss >> word){
        //pesquisa a palavra na tabela de vocabularios e pega os documentos que ela eh presente
        palavraAux = TabelaVocab->Pesquisa(word);
        listaDocumentos = palavraAux->getDocumentos();

        aux = listaDocumentos.primeiro;

        //itera por cada documento que possui a palavra
        while(aux != nullptr){
            float soma = 0;
            float resultado;
            
            //a chave passa a ser o nome do arquivo
            chave = aux->nomeArquivo;
            documento = this->Pesquisa(chave);

            //pega o valor de Wtd e divide por Wd acrescenta ao resultado atrelado ao documento
            soma += documento->indice.getWtd(word);
            resultado = soma/documento->Wd;

            //para consultas com multiplas palavras, se a lista ja possui algum valor dentro dela
            //basta somar com o resultado encontrado na segunda consulta
            if(listaResultados.Pesquisa(chave)->resultado == 0){
                listaResultados.InsereFinal(chave,resultado);
            }
            else{
                listaResultados.Pesquisa(chave)->resultado += resultado;
            }

            aux = aux->prox;
        }


    }

    return listaResultados;


}
