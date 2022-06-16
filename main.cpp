#include <iostream>
#include <fstream>
#include "ListaEncadeadaSimples.h"
using namespace std;

int main()
{
        ListaEncadeadaSimples listaCaracteres;
        tabelaLetras tabela;

        //Leitura do documento
        ifstream is("arquivoTexto.txt");
        int repeticoesNoTexto;
        char caractere;

        while (is.get(caractere)){
            repeticoesNoTexto = 0;
             listaCaracteres.addLetraTextoOriginal(caractere);
            if(!listaCaracteres.estaNaLista(caractere)){
                ifstream as("arquivoTexto.txt");
                char caractereAnalisado = caractere;

                repeticoesNoTexto = 0;
                int cont = 0;
                while (as.get(caractere)){
                    if(caractere == caractereAnalisado){
                        repeticoesNoTexto++;
                    }
                    cont++;
                }
                listaCaracteres.adicionarOrdenadoHuffmann(caractereAnalisado,repeticoesNoTexto);
                as.close();
            }
        }
        listaCaracteres.imprimirLista();
        listaCaracteres.criarArvoreHuffmann();
        listaCaracteres.imprimirLista();

        listaCaracteres.imprime(listaCaracteres.inicio);
        listaCaracteres.popularTabelaCodigos(listaCaracteres.inicio,"",tabela);
        tabela.imprimeTabela();
        is.close();


        cout << listaCaracteres.getTextoTransformado(tabela) <<endl;

    return 0;
}
