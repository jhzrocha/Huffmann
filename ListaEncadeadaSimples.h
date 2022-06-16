#ifndef LISTAENCADEADASIMPLES_H_INCLUDED
#define LISTAENCADEADASIMPLES_H_INCLUDED

struct ElementoLetraRepeticoes{
    int qtdRepeticoes = 0;
    char letra = 0;
    ElementoLetraRepeticoes *prox = nullptr;
    ElementoLetraRepeticoes *esq = nullptr;
    ElementoLetraRepeticoes *dir = nullptr;
    ElementoLetraRepeticoes *pai = nullptr;

};

struct tabelaLetras{
     char letrasEncontradas[256];
    std::string codigoHuffmann[256];
    int quantidadeLetras = 0;

    void addLetra(char letra, std::string codigoHuffmanEncontrado){
        letrasEncontradas[quantidadeLetras] = letra;
        codigoHuffmann[quantidadeLetras] = codigoHuffmanEncontrado;
        this->quantidadeLetras++;
    }

    void imprimeTabela(){
        std::cout << "____Tabela de Dados_____" << std::endl;
        for(int i = 0; i <= quantidadeLetras-1; i++){
            std::cout << letrasEncontradas[i] << "  -  ";
            std::cout << codigoHuffmann[i];
            std::cout << std::endl;
        }
    }

    std::string getCodigoByChar(char letra){
        for(int i = 0; i < this->quantidadeLetras; i++){
            if(letrasEncontradas[i] == letra){
                return codigoHuffmann[i];
            }
        }
    }
};



struct ListaEncadeadaSimples{
    ElementoLetraRepeticoes *inicio = nullptr;

    int quantidadeLetras = 0;
    char textoOriginalEmChar[1000];


    void addLetraTextoOriginal(char letra){
        textoOriginalEmChar[quantidadeLetras] = letra;
        quantidadeLetras++;
    }

    ElementoLetraRepeticoes* getPtrFinalLista(){
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        nav = this->inicio;

        while(nav->prox != nullptr){
            nav = nav->prox;
        }
        return nav;
    }

    void adicionarFim(char letra, int nrRepeticoes){
        ElementoLetraRepeticoes *novo = new ElementoLetraRepeticoes();
        ElementoLetraRepeticoes * ultimoElemento = this->getPtrFinalLista();

        novo->letra = letra;
        novo->qtdRepeticoes = nrRepeticoes;

        ultimoElemento->prox = novo;
    }

    void adicionarInicio(char letra, int nrRepeticoes){
        ElementoLetraRepeticoes *novo = new ElementoLetraRepeticoes();
        novo->prox = this->inicio;
        novo->letra = letra;
        novo->qtdRepeticoes = nrRepeticoes;

        this->inicio= novo;
    }

    int getQuantidadeElementos(){
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        nav = this->inicio;
        int contador = 0;
        while(nav != nullptr){
            contador++;
            nav = nav->prox;
        }
        return contador;
    }

    bool estaNaLista(char letra){
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        nav = this->inicio;

        while(nav != nullptr){
            if(nav->letra == letra){
                return true;
            }else{
                nav = nav->prox;
            }
        }
        return false;
    }

    void popularTabelaCodigos(ElementoLetraRepeticoes* no,std::string codigo,tabelaLetras &tabela){
        if(no != nullptr) {
            if(no->dir == nullptr  && no->letra!= 0){
                tabela.addLetra(no->letra,codigo);
                std::cout <<no->letra<<" = "<<codigo<<std::endl;
            } else {
                popularTabelaCodigos(no->esq,codigo+"0",tabela);
                popularTabelaCodigos(no->dir,codigo+"1",tabela);
            }
        }
    }

    std::string getTextoTransformado(tabelaLetras &tabela){

        std::string textoTransformado = "";
        int cont = 0;

        while(cont < quantidadeLetras){
            textoTransformado = textoTransformado + " "+ tabela.getCodigoByChar(textoOriginalEmChar[cont]);
            cont++;
        }
        return textoTransformado;
    }

    bool estaNaListaRepeticoes(int repeticoes){
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        nav = this->inicio;

        while(nav != nullptr){
            if(nav->qtdRepeticoes == repeticoes){
                return true;
            }else{
                nav = nav->prox;
            }
        }
        return false;
    }

    void adicionarNaPosicao(int posicao, char letra, int nrRepeticoes){
        ElementoLetraRepeticoes *novo = new ElementoLetraRepeticoes();
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        int maiorElemento = this->getQuantidadeElementos();

        if (posicao > (maiorElemento - 1)){
            std::cout << "Não é possível adicionar nesta posição" << std::endl;
        }else{
            int contador = 0;

            while (contador != posicao - 1){
                nav = nav->prox;
                contador++;
            }

            if(nav->prox != nullptr){
                novo->prox = nav->prox;
            }

            nav->prox = novo;
            novo->letra = letra;
            novo->qtdRepeticoes = nrRepeticoes;
        }
    }

    void criarArvoreHuffmann(){
       while(this->getQuantidadeElementos() > 1){
            ElementoLetraRepeticoes *novoElemento = new ElementoLetraRepeticoes();
            ElementoLetraRepeticoes *primeiroElemento = this->inicio;
            ElementoLetraRepeticoes *segundoElemento = primeiroElemento->prox;
            this->inicio = segundoElemento->prox;

            primeiroElemento->pai = novoElemento;
            segundoElemento->pai = novoElemento;
            novoElemento->esq = primeiroElemento;
            novoElemento->dir = segundoElemento;

            novoElemento->qtdRepeticoes = primeiroElemento->qtdRepeticoes + segundoElemento->qtdRepeticoes;

            this->adicionarElementoArvoreHuffmann(novoElemento);
        }
    }

    void adicionarOrdenadoHuffmann(char letra, int qtdRepeticoes){
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        ElementoLetraRepeticoes *novo = new ElementoLetraRepeticoes();

        novo->letra = letra;
        novo->qtdRepeticoes = qtdRepeticoes;

        nav = this->inicio;

        if((nav == nullptr) || (this->inicio->qtdRepeticoes >= qtdRepeticoes)){
            this->adicionarInicio(letra,qtdRepeticoes);
        } else{
            while(nav != nullptr){
                if( nav->prox != nullptr && nav->prox->qtdRepeticoes >= qtdRepeticoes){
                    novo->prox = nav->prox;
                    nav->prox = novo;
                    break;
                }else{
                    if(nav->prox == nullptr){
                        this->adicionarFim(letra,qtdRepeticoes);
                        break;
                    }
                }
                nav = nav->prox;
            }
        }
    }

    void adicionarElementoArvoreHuffmann(ElementoLetraRepeticoes *elemento){
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();

        nav = this->inicio;

        if((nav == nullptr) || (this->inicio->qtdRepeticoes >= elemento->qtdRepeticoes)){
            elemento->prox = this->inicio;
            this->inicio= elemento;
        } else{
            while(nav != nullptr){
                if(nav->prox != nullptr && nav->prox->qtdRepeticoes >= elemento->qtdRepeticoes){
                    elemento->prox = nav->prox;
                    nav->prox = elemento;
                    break;
                }else{
                    if(nav->prox == nullptr){
                        ElementoLetraRepeticoes * ultimoElemento = this->getPtrFinalLista();
                        ultimoElemento->prox = elemento;
                        break;
                    }
                }
                nav = nav->prox;
            }
        }
    }

    bool getCodigoLetra(ElementoLetraRepeticoes *elementoComLetra){
        bool enderecoNavegadorTemp[128];

        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        ElementoLetraRepeticoes *nav2 = new ElementoLetraRepeticoes();
        int contador = 0;

        nav = elementoComLetra;
        nav2 = elementoComLetra;

        while(nav->pai != nullptr){
            if(nav->esq = nav2){
                enderecoNavegadorTemp[contador] = 0;
            }
            if(nav->dir = nav2){
                enderecoNavegadorTemp[contador] = 1;
            }
            nav2 = nav;
            nav = nav->pai;
        }

        bool temp[128];
        int cont= 0;
        for(int i = 128; i >= 0; i--){
            if(enderecoNavegadorTemp[i]!= NULL){
                temp[cont] = enderecoNavegadorTemp[i];
                cont++;
            }
        }
        return temp;
    }

    void imprime (ElementoLetraRepeticoes *h) {
       if (h == NULL){
        return;
       }
       std::cout << h->letra << std::endl;
       imprime(h->esq);
       imprime(h->dir);
    }
    char getPorPosicao(int posicao){
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        int maiorElemento = this->getQuantidadeElementos();

        nav = this->inicio;
        if (posicao > (maiorElemento - 1)){
            std::cout << "Não é possível pegar nesta posição" << std::endl;
        }else{
            int contador = 0;

            while (contador != posicao){
                nav = nav->prox;
                contador++;
            }

            return nav->letra;
        }
    }
    void removeInicio(){
        ElementoLetraRepeticoes * primeiroElemento;
        primeiroElemento = this->inicio;
        this->inicio = this->inicio->prox;

        delete primeiroElemento;
    }
    void removeFim(){
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        nav = this->inicio;
        while(nav != nullptr){
            if(nav->prox->prox == nullptr ){
                ElementoLetraRepeticoes * ultimoElemento;
                ultimoElemento = nav->prox;
                nav->prox = nullptr;
                delete ultimoElemento;
                break;
            }
            nav = nav->prox;
       }
    }
    void removePosicao(int posicao){
        ElementoLetraRepeticoes *nav,*anterior = new ElementoLetraRepeticoes();
        int maiorElemento = this->getQuantidadeElementos();
        nav = this->inicio;
        if (posicao > (maiorElemento - 1)){
            std::cout << "Não é possível remover nesta posição" << std::endl;
        }else{
            int contador = 0;
            ElementoLetraRepeticoes *elementoDeletado;
            while (contador != posicao){
                if(contador + 1 == posicao){
                    anterior = nav;
                    elementoDeletado = nav;
                }
                contador++;
                nav = nav->prox;
            }
            delete elementoDeletado;
            anterior->prox = nav->prox;
        }
    }
    void imprimirLista(){
        ElementoLetraRepeticoes *nav = new ElementoLetraRepeticoes();
        nav = this->inicio;
        std::cout << "Letra , QtdRepeticoes" << std::endl;
        while(nav != nullptr){
            std::cout << nav->letra <<"   "<<nav->qtdRepeticoes << std::endl;
            nav = nav->prox;
       }
    }
};
#endif // LISTAENCADEADASIMPLES_H_INCLUDED
