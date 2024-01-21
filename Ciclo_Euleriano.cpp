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
    
    Este arquivo contem a implementacao dos metodos necessarios
    para verificar se um grafo eh euleriano e encontrar um tour
    de euler em um grafo euleriano.
*/


#include "Grafos.cpp"



/*  Classe de algoritmos para resolver os
    problemas que envolvem ciclos eulerianos.   */
class Ciclo_Euleriano {

    private: ll K;              // Quantidade de vertices no 'subgrafo de euler' do grafo 'G'.
    private: ll Raiz;           // Indicador do vertice de partida do tour.
    public:  Grafos *G;         // G: Representacao computacional de um grafo.
    private: ll Ponte_v;        // Indicador de que um vertice 'V' eh extremidade de uma ponte.
    private: ll Ponte_w;        // Indicador de que um vertice 'W' eh extremidade de uma ponte.
    private: vector<ll> Tour;   // Vetor de vertices que representam o 'Tour de Euler' no grafo.


    /*  Construtor da classe.   */
    //============================
    public: Ciclo_Euleriano(Grafos *G, ll Inicio = 0){
        this->G = G;
        this->K = G->QV;
        this->Ponte_v = -1;
        this->Ponte_w = -1;
        this->Raiz = Inicio;
        this->Tour.push_back(Inicio);   // Vertice raiz do tour.
    }


    /*  Metodo para verificar se todos
        os vertices do grafo sao pares.
        (CONDICAO PARA UM GRAFO SER EULERIANO)  */
    //============================================
    public: bool Verificar_Graus_Pares_(){

        ll i = this->G->QV;
        bool Vertices_Pares = true; // Indica que o grafo eh euleriano (inicialmente).

        while(--i > -1){

            // Verifica se algum vertice tem grau impar.
            if((this->G->Vert[i].Grau % 2) != 0){
                Vertices_Pares = false; // Indica que o grafo nao eh euleriano (conclusao).
                break;
            }
        }

        return Vertices_Pares;
    }
    
    
    /*  Metodo para realizar o percurso
        em profundidade no grafo.    */
    //=================================
    void Percurso_Profundidade_(ll V, ll &Alc, vector<ll> &Alcancados){

        Alcancados[V] = ++Alc;  // Indica que o vertice foi alcancados.

        // Loop: Percorre a lista de adjacencia de V.
        for(auto& W: this->G->Vert[V].Adj){

            // Verifica se o vertice W nao foi alcancado.
            if(Alcancados[W] == 0){

                /*  PONTES:
                    Uma aresta (V, W), ou (W, V), é ignorada no percurso
                    em profundidade caso esteja indicada, como possivel
                    ponte, nas variaveis 'Ponte_v' e 'Ponte_w'.         */
                //========================================================
                if(!(((Ponte_v == V) && (Ponte_w == W)) || ((Ponte_v == W) && (Ponte_w == V))))
                    Percurso_Profundidade_(this->G->Vert[W].No, Alc, Alcancados);   // Explora o grafo em profundidade.
            }
        }
    }


    /*  Metodo para verificar se o grafo eh
        conexo usando percurso em profundidade.
        (CONDICAO PARA UM GRAFO SER EULERIANO)  */
    //============================================
    public: bool Verificar_Grafo_Conexo_(){

        ll Alc = 0;                             // Numero de vertices alcancados.
        vector<ll> Alcancados(this->G->QV, 0);  // Vetor para indicar se um vertice ja foi alcancado.

        this->Percurso_Profundidade_(this->G->Vert[Raiz].No, Alc, Alcancados);

        /*  Verifica se todos os vertices, no
            subgrafo de euler, foram alcancados.    */
        //============================================
        if(Alc != this->K) return false;    // Desconexo.
        return true;                        // Conexo.
    }


    /*  Metodo para verificar se uma aresta
        (V, W), do grafo, eh uma ponte. */
    //=====================================
    bool Verificar_Ponte_(int V, int W){

        /*  PONTES:
            Indicacao das extremidades de uma possivel ponte.
            A aresta (V, W) passa a ser ignorada no percurso
            em profundidade para verificar se o subgrafo de
            de euler continua conexo sem a aresta.  */
        //===================================================
        this->Ponte_v = V;
        this->Ponte_w = W;

        // Verifica se o grafo se torna desconexo.
        if(Verificar_Grafo_Conexo_() == false) return true; // A aresta eh realmente uma ponte.
        return false;                                       // A aresta nao eh uma ponte.
    }
    
    
    /*  Metodo para encontrar um tour
        de euler em um grafo euleriano. */
    //====================================
    public: void Tour_Euler___FLEURY_(){

        ll V, W;            // Extremidades de uma aresta.
        set<ll> *Arestas;   // Lista de adjacencia auxiliar.

        // Loop: Enquanto houver arestas no grafo.
        while(this->G->QE != 0){
            
            V       = Tour.back();              // ESCOLHA DE UM VERTICE:       Ultimo vertice alcancado no tour.
            Arestas = &(this->G->Vert[V].Adj);  // ESCOLHA DAS ARESTAS (V, W):  Lista de arestas para iniciar o tour.

            // Loop: Percorre a lista de adjacencia de V.
            for(auto& auxW: (*Arestas)){

                /*  A aresta (V, W) eh escolhida se existe
                    apenas ela, ou se (V, W) nao eh ponte.  */
                if(((*Arestas).upper_bound(auxW) == (*Arestas).end())
                || (Verificar_Ponte_(V, auxW) == false)){
                    W = auxW;
                    break;
                }
            }

            // Remocao da aresta (V, W) do subgrafo.
            //===========================================
            this->G->Remover_Aresta_(V, W); // Remove a aresta (V, W) de G.
            this->G->Remover_Aresta_(W, V); // Remove a aresta (W, V) de G.
            this->Tour.push_back(W);        // Insere a aresta (V, W) no Tour.

            /*  Verifica se V nao possui mais vertices
                adjacentes apos a remocao da aresta (V, W). */
            if((this->G->Vert[V].Grau == 0))
                this->K--;  // Nesse caso atualiza-se o numero de vertices no subgrafo de euler do grafo G.
        }
    }
    
    
    /*  Metodo para imprimir o
        tour de euler encontrado.   */
    //================================
    public: void Imprimir_Tour_Euler_(){

        cout << endl;
        cout << "|-| ============== |-|" << endl;
        cout << "|-| TOUR DE EULER:     ";
        for(auto& Vert: this->Tour)
            cout << " " << Vert +1;
        cout << "\n|-| ============== |-|" << endl;
    }


    /*  Destructor da classe.   */
    //============================
    public: ~Ciclo_Euleriano(){

        this->Tour.clear();
        delete(this->G);
    }
};