#include <iostream>
#include <fstream>
#include "ListaEncadeadaSimples.h"
using namespace std;

int main()
{
        ArvoreHuffmann listaCaracteres;
        tabelaLetras tabela;
        cout << "Texto Original: " << endl;
        cout << endl;
        //Leitura do documento
        ifstream is("arquivoTexto.txt");
        int repeticoesNoTexto;
        char caractere;

        while (is.get(caractere)){
            repeticoesNoTexto = 0;
             listaCaracteres.addLetraTextoOriginal(caractere);
             cout << caractere;
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
        cout << endl;
        cout <<endl <<"Aparições no texto" << endl;
        listaCaracteres.imprimirLista();
        cout << "--------------------------" << endl;

        listaCaracteres.criarArvoreHuffmann();

        listaCaracteres.popularTabelaCodigos(listaCaracteres.inicio,"",tabela);
        tabela.imprimeTabela();
        is.close();

        cout << "--------------------------" << endl;
        cout << "Texto Transformado: " << endl;
        listaCaracteres.transformarTexto(tabela);
        listaCaracteres.imprimirTextoTransformado();


        cout << endl;
        ofstream out("TextoTransformado.txt");
        out << listaCaracteres.getArquivoTransformadoEmString();
        out.close();
        cout << "Texto Salvo em TextoTransformado.txt"<< endl;
        cout << endl;
        ofstream tabelaOut("Tabela.txt");
        tabelaOut << tabela.tabelaStringParaTXT();
        tabelaOut.close();
        cout << "Tabela Salva em Tabela.txt"<< endl;

        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl<<"*****************DECODIFICAcaO*****************" << endl;
        Decodificador decodificador;

        cout << "Abrindo Tabela.txt" << endl;
        cout << endl;
        ifstream tab("Tabela.txt");
        while (tab.get(caractere)){
            char letraAnalisada;
            if(caractere != '0' && caractere != '1' && caractere != NULL){
                letraAnalisada = caractere;
            }
            if(caractere !=0 && letraAnalisada!=0 && letraAnalisada!= caractere){
                decodificador.popularTabelas(letraAnalisada,caractere);
            }
        }
        tab.close();
        cout << endl;
        cout << "--------------------------" << endl;
        cout << endl;
        cout << "Tabela Gerada a partir da Tabela.txt: " << endl;
        decodificador.imprimirTabela();

        decodificador.criarArvoreHuffmann();
        cout << endl;
        cout << "--------------------------" << endl;
        cout << endl;
        cout << "Texto Codificado retirado de TextoTransformado.txt:" << endl;
        ifstream txtTransformado("TextoTransformado.txt");
        while (txtTransformado.get(caractere)){
            cout << caractere;
            decodificador.inTextoCodificado(caractere);
        }

        txtTransformado.close();
        cout << endl;
        cout << "--------------------------" << endl;
        cout << endl;
        cout << "Texto Decodificado:";
        cout << decodificador.decodificarPelaArvore();

        cout << endl;
        cout << endl;


    return 0;
}
