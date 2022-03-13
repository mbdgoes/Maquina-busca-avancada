#include <string>

//bibliotecas usadas para manipulacao de string e arquivos
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include <getopt.h>

using namespace std;

//Esse arquivo contem algumas funcoes para o tratamento dos dados e contagem dos arquivos

bool isASCII (char c) {  
    return !(c>=0 && c <128);   
}


int getQuantidadeArquivos(const char *path) {
    int count = 0;
    int total = 0;
    struct dirent *entry;
    DIR *dir = opendir(path);
    string text;
    string nomeArquivo;

    if (dir == NULL) {
        cout << "ERRO: Pasta Vazia";
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        if(count >= 2){
            total++;
        }
        else{
            count++;
        }
    }

    closedir(dir);
    
    return total;
}

int getTamanhoVocabulario(const char *path) {
    int count = 0;
    int tamanho = 0;
    struct dirent *entry;
    DIR *dir = opendir(path);
    string text;
    string nomeArquivo;

    
    if (dir == NULL) {
        return 0;
    }


    while ((entry = readdir(dir)) != NULL) {
        if(count >= 2){
            nomeArquivo = entry->d_name;
            ifstream file(path + nomeArquivo);
            getline(file,text);
            text.erase(remove_if(text.begin(), text.end(), ::ispunct), text.end());
            text.erase(remove_if(text.begin(), text.end(), ::isdigit), text.end());
            text.erase(remove_if(text.begin(), text.end(), isASCII), text.end());
            transform(text.begin(),text.end(),text.begin(),::tolower);

            istringstream ss(text);
            string word;

            while(ss >> word){
                tamanho++;
            }
            file.close();

        }
        else{
            count++;
        }
    }

    closedir(dir);

    return tamanho;
}

int getTamanhoStopWords(const char *path) {
    ifstream file(path);
    string word;
    int tamanho = 0;

    while(file >> word){
        tamanho++;
    }
    file.close();

    return tamanho;
}

void parse_args(int argc, char* argv[],char** argumentos){
    int opt;
    while((opt = getopt(argc,argv,"i:o:c:s:"))!=-1){
        switch(opt){
            case 'i':
                argumentos[0] = optarg;
                break;
            case 'o':
                argumentos[1] = optarg;
                break;
            case 'c':
                argumentos[2] = optarg;
                break;
            case 's':
                argumentos[3] = optarg;
                break;
        }

    }
}

char* checarBarra(char* argumento){
    string str(argumento);
    int ultimocaractere;

    ultimocaractere = str.length() - 1;

    if(str[ultimocaractere] == '/'){
        return strdup(str.c_str());
    }

    else str.push_back('/');
    
    return strdup(str.c_str());

}