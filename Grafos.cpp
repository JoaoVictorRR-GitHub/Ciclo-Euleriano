/*
    @ Docente:
        * Joao Patricio.
    @ Estudante:
        * Joao Victor do Rozario Recla.
    @ Disciplina:
        * Analise e Sintese de Algoritmos.
    @ Instituicao:
        * IPT  - Instituto Politecnico de Tomar.
        * ESTA - Escola Superior de Tecnologia de Abrantes.
    
    Este arquivo contem uma representacao computacional da
    estrutura de um grafo com a implementacao dos metodos
    necessarios para a sua construcao.
*/


#include <iostream>
#include <vector>
#include <ctime>
#include <set>

using namespace std;

#define ll long long int
#define SEM_MEMORIA cout << ("[x_x] SEM MEMÓRIA PARA ESSE PROCEDIMENTO NO MOMENTO!\n") << endl;



/*  Estrutura de um Vertice.    */
typedef struct Vertice{

    ll No;          // Identificador do vertice.
    ll Grau;        // Grau do vertice.
    set<ll> Adj;    // Lista de adjacencia do vertice.

    // Construtor.
    Vertice(ll Indicador = 0){

        this->No = Indicador;
        this->Grau = 0;
    };
}Vertice;


/*  Classe de grafos.   */
class Grafos {

    public: ll QV;  // Quantidade de vertices.
    public: ll QE;  // Quantidade de arestas.
    Vertice *Vert;  // Vetor de vertices.


    /*  Metodo responsavel por criar e
        inicializar a estrutura do grafo.   */
    //========================================
    public: Grafos(ll V){

        // Inicializacao das variaveis.
        this->QV  = V;
        this->QE  = 0;
        this->Vert = new Vertice[V]();

        if(this->Vert)
            for(ll i = 0; i < this->QV; i++)
                this->Vert[i].No = i;   // Identificacao dos vertices (Para imprimir).
        else SEM_MEMORIA
    }


    /*  Metodo para gerar um grafo
        completamente aleatorio.    */
    //================================
    public: void Gerar_Grafo_Aleatorio(){

        srand(time(NULL));                      // Semente para geracao de numeros aleatorios.
        
        ll V, W;
        ll E = (this->QV * (this->QV-1)) / 2;   // Numero maximo de arestas.
        E = rand() % E +1;                      // Numero definitivo de arestas.

        // Geracao aleatoria dos vertices do grafo.
        while(E != -1){

            V = rand() % this->QV;  // Vertice de partida.
            W = rand() % this->QV;  // Vertice de chegada.

            Inserir_Aresta_(V, W);  // Insercao da aresta (V, W).
            Inserir_Aresta_(W, V);  // Insercao da aresta (W, V).
            
            if(V != W)  E--;
        }
    }


    /*  Metodo responsavel por inserir
        uma aresta (V, W) no grafo. */
    //================================
    public: void Inserir_Aresta_(int V, int W){

        if(V != W){

            set<ll> *Aux = &(this->Vert[V].Adj);

            // Se o vertice W nao existe na lista.
            if((*Aux).find(W) == (*Aux).end()){

                this->QE++;             // Atualiza a quantidade de arestas no grafo.
                (*Aux).insert(W);       // Insere W na lista de adjacencia de V.
                this->Vert[V].Grau++;   // Atualiza o grau do vertice V.
            }
        }
    }
    
    
    /*  Metodo responsavel por remover
        uma aresta (V, W) do grafo. */
    //================================
    public: void Remover_Aresta_(int V, int W){

        set<ll> *Aux = &(this->Vert[V].Adj);

        // Se o vertice W existe na lista.
        if((*Aux).find(W) != (*Aux).end()){

            this->QE--;             // Atualiza a quantidade de arestas no grafo.
            (*Aux).erase(W);        // Remove W da lista de adjacencia de V.
            this->Vert[V].Grau--;   // Atualiza o grau do vertice V.
        }
    }
    
    
    /*  Metodo responsavel por imprimir a estrutura
        do grafo exibindo as listas de adjacencias. */
    //================================================
    public: void Imprimir_Grafo_(){

        cout << endl;
        cout << "|-| ============= |-|" << endl;
        cout << "|-| Grafo G:      |-|" << endl;
        cout << "|-| ============= |-|" << endl;
        for(ll V = 0; V < this->QV; V++){

            // Imprime o vertice de partida, V.
            cout << "    " << V+1 << ":";

            // Loop: Imprime a lista de adjacencia de V.
            for(auto& VertAdj: this->Vert[V].Adj)
                cout << " " << VertAdj +1;
            cout << endl;
        }
        cout << "|-| ============= |-|" << endl;
    }


    /*  Metodo responsavel por deletar a estrutura
        do grafo removendo as listas de adjacencias.    */
    //====================================================
    public: ~Grafos(){

        // Deleta as listas de adjacencias de cada vertice do Grafo.
        for(ll V = 0; V < this->QV; V++)
            this->Vert[V].Adj.clear();
    }
};