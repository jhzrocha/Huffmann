#include <iostream>
#include <fstream>
#include "ListaEncadeadaSimples.h"
using namespace std;

int main()
{
        ListaEncadeadaSimples listaCaracteres;

        //Leitura do documento
        ifstream is("arquivoTexto.txt");
        int repeticoesNoTexto;
        char caractere;
        while (is.get(caractere)){
            repeticoesNoTexto = 0;
            if(!listaCaracteres.estaNaLista(caractere)){
                ifstream as("arquivoTexto.txt");
                char caractereAnalisado = caractere;

                repeticoesNoTexto = 0;

                while (as.get(caractere)){
                    if(caractere == caractereAnalisado){
                        repeticoesNoTexto++;
                    }
                }
                listaCaracteres.adicionarOrdenadoHuffmann(caractereAnalisado,repeticoesNoTexto);
                as.close();
            }
        }
        listaCaracteres.imprimirLista();
        listaCaracteres.criarArvoreHuffmann();
        listaCaracteres.imprimirLista();
        is.close();

        cout << listaCaracteres.getQuantidadeElementos();

    return 0;
}
