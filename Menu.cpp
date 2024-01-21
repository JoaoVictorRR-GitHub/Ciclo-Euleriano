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
    
    Este arquivo contem a implementacao do menu principal
    que disponibiliza os meios para criar e testar alguns
    dos metodos, de grafo e ciclo euleriano, implementados.
*/


#include "Ciclo_Euleriano.cpp"

Grafos *G;



/*  Menu para decidir se o grafo
    sera gerado aleatoriamente. */
//================================
bool Escolher_Grafo_Aleatorio(){

    string Escolha;
    bool Grafo_Aleatorio = false;

    while(1){
        // Escolha.
        cout << "\n|--| Deseja gerar um grafo aleatório ? [SIM / NAO]" << endl;
        cout << "|--| ";
        cin >> Escolha;

        // Decisoes.
        if((Escolha == "SIM") || (Escolha == "sim")){
            Grafo_Aleatorio = true;
            break;
        }
        if((Escolha == "NAO") || (Escolha == "nao"))
            break;
    }

    return Grafo_Aleatorio; // Resultado.
}


/*  Menu para criacao do grafo. */
//================================
void Criar_Grafo(){

    ll V, W;    // Vertices.
    ll N, M;    // Numero de vertices e arestas.
    
    // Tamanho do grafo.
    cout << "\n|--| Informe a quantidade de vértices do grafo:  ";
    cin >> N;
    G = new Grafos(N);

    // Escolha do grafo.
    if(Escolher_Grafo_Aleatorio() == true)
        G->Gerar_Grafo_Aleatorio();
    else{
        // Numero de arestas.
        cout << "\n\n|--| Informe a quantidade de arestas do grafo: ";
        cin >> M;
        
        // Loop: Insercao dos vertices.
        while(M-- > 0){
            cout << "\n|--| ================================== (0" << M+1 << ")" << endl;
            cout << "|--| Informe o vertice de partida:    ";
            cin >> V;
            cout << "|--| Informe o vertice de chegada:    ";
            cin >> W;

            // Verifica se os vertices estao dentro dos limites.
            if((V <= G->QV) && (W <= G->QV) && (V > 0) && (W > 0)){
                V--; W--;   // Indexacao.
                G->Inserir_Aresta_(V, W);
                G->Inserir_Aresta_(W, V);
            }
            else{
                M++;
                cout << "|--| [INTERVALO DE VÉRTICES INVALIDO !]" << endl;
            }
        }
    }

    // Imprime o grafo criado.
    G->Imprimir_Grafo_();
}



/*  Main.   */
//============
int main(){

    Criar_Grafo();
    Ciclo_Euleriano *Ciclo = new Ciclo_Euleriano(G);

    // Verifica se o grafo eh um grafo de euler.
    //  * (Se eh Conexo e se todos os vertices tem grau par).
    if(Ciclo->Verificar_Grafo_Conexo_() && Ciclo->Verificar_Graus_Pares_()){

        Ciclo->Tour_Euler___FLEURY_();  // Encontra o tour de euler no grafo.
        Ciclo->Imprimir_Tour_Euler_();  // Imprime o tour.
    }
    else cout << "\n|-| O GRAFO NÃO É EULERIANO." << endl;
    
    delete(Ciclo);
    return 0;
}