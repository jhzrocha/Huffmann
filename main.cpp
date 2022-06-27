#include <iostream>
#include <fstream>
#include "ListaEncadeadaSimples.h"
using namespace std;

int main()
{
        ArvoreHuffmann listaCaracteres;
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


        listaCaracteres.transformarTexto(tabela);
        listaCaracteres.imprimirTextoTransformado();

        ofstream out("TextoTransformado.txt");
        out << listaCaracteres.getArquivoTransformadoEmString();
        out.close();

        ofstream tabelaOut("Tabela.txt");
        tabelaOut << tabela.tabelaStringParaTXT();
        tabelaOut.close();


        cout << endl<<"*****************DECODIFICAcaO*****************" << endl;
        Decodificador decodificador;
        ifstream tab("Tabela.txt");

        while (tab.get(caractere)){
            char letraAnalisada;
            if(caractere != '0' && caractere != '1' && caractere != NULL){
                letraAnalisada = caractere;
            }
            if(caractere !=0 && letraAnalisada!=0 && letraAnalisada!= caractere){
                cout <<"Caractere:" <<caractere << "," << "Letra:" <<letraAnalisada << endl;
                decodificador.popularTabelas(letraAnalisada,caractere);
            }
        }
        tab.close();

        decodificador.imprimirTabela();
        decodificador.criarArvoreHuffmann();
        decodificador.imprimeArvore(decodificador.inicio);

        ifstream txtTransformado("TextoTransformado.txt");

        while (txtTransformado.get(caractere)){
            decodificador.inTextoCodificado(caractere);
        }

        txtTransformado.close();


        cout << "Texto Decodificado:";
        cout << decodificador.decodificarPelaArvore();


    return 0;
}
