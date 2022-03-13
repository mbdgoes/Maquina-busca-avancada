#include <iostream>

#include "TabelaHash.hpp"
#include "ListaEncadeada.hpp"
#include "Palavra.hpp"
#include "ListaConsulta.hpp"
#include "FuncoesTamanhoArquivos.hpp"

using namespace std;

int main(int argc, char* argv[]){

    char* argumentos[4];
    parse_args(argc,argv,argumentos);

    //armazenamento dos argumentos da linha de comando
    char* pathConsulta = argumentos[0];
    char* pathOutput = argumentos[1];
    char* pathCorpus = argumentos[2];
    char* pathCorpusComBarra = checarBarra(argumentos[2]);
    char* pathStopWords = argumentos[3];

    int tamanhoStopWords = getTamanhoStopWords(pathStopWords);
    int tamanhoVocabulario = getTamanhoVocabulario(pathCorpusComBarra);
    int tamanhoCorpus = getQuantidadeArquivos(pathCorpus);

    //Inicializacao das TabelaHash
    TabelaHash HashMapStopWords(tamanhoStopWords);
    TabelaHash HashVocabulario(tamanhoVocabulario);
    TabelaHash HashArquivos(tamanhoCorpus);


    string chave;
    ifstream file(pathStopWords);
    Palavra palavra;

    //popula o Hash de stopWords
    while(file >> chave){
        palavra.chave = chave;
        HashMapStopWords.Insere(palavra,"0");
    }
    file.close();


    //popula o Hash de vocabulario
    int count = 0;
    struct dirent *entry;
    DIR *dir = opendir(pathCorpus);
    string text;
    string nomeArquivo;

    while ((entry = readdir(dir)) != NULL) {
        if(count >= 2){
            nomeArquivo = entry->d_name;

            ifstream file(pathCorpusComBarra + nomeArquivo);
            getline(file,text);
            //remocao dos elementos que nao serao usados na string
            text.erase(remove_if(text.begin(), text.end(), ::ispunct), text.end());
            text.erase(remove_if(text.begin(), text.end(), ::isdigit), text.end());
            text.erase(remove_if(text.begin(), text.end(), isASCII), text.end());
            transform(text.begin(),text.end(),text.begin(),::tolower);

            istringstream ss(text);
            string word;

            while(ss >> word){
                //checa se palavra esta nas stopwords, se estiver nao continua
                Palavra *ptr = HashMapStopWords.Pesquisa(word);
                if(ptr->chave == "-1"){
                    Palavra novoVocabulario;
                    novoVocabulario.chave = word;
                    HashVocabulario.Insere(novoVocabulario,nomeArquivo);

                    Palavra arquivo;
                    arquivo.chave = nomeArquivo;
                    HashArquivos.Insere(arquivo,word);

                    delete ptr;
                }

            }
            file.close();

        }
        else{
            count++;
        }
    }

    closedir(dir);

    string consulta;
    ifstream arquivoConsulta(pathConsulta);
    getline(arquivoConsulta,consulta);
    arquivoConsulta.close();

    //calculo do Wtd e do Wd para cada palavra
    HashArquivos.calcularWtd(&HashVocabulario,tamanhoCorpus);
    HashArquivos.calcularWd();

    ListaConsulta listaResultados;
    listaResultados = HashArquivos.Consultar(consulta,&HashVocabulario);


    std::ofstream out(pathOutput);
    std::cout.rdbuf(out.rdbuf());

    //ordenacao e impressao do resultados no pathOutput
    listaResultados.Ordena(&listaResultados.primeiro);
    listaResultados.Imprime();

}
