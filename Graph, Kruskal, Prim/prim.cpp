//prim
#include <iostream>
#include <fstream>

using namespace std;

string city[9] = {"Butynga", "Klajpeda", "Taurogi",
                  "Szawle","Poniewiez", "Uciana",
                  "Kowno", "Mariampol", "Wilno"};

#define matrixSize 9

class Graph {
public:
    int min(int *key, bool *tree){
        int min = INT_MAX, minim;

        for (int i = 0; i < matrixSize; i++)
            if (tree[i] == false && key[i] < min)
                min = key[i], minim = i;
        return minim;
    }

    void show(int *parent, int g[matrixSize][matrixSize]){
        int cost = 0;
        for (int i = 1; i < matrixSize; i++) {
            cout << city[i] << " -> " << city[i - 1] << " (" << g[i][parent[i]] << ")" << endl;
            cost+=g[i][parent[i]];

        }
        cout<<endl<<"Entire route: "<<cost<<endl;
    }

    void prim_algorithm(int **graph){

        int parent[matrixSize], key[matrixSize];

        bool minimaltree[matrixSize];

        for (int i = 0; i < matrixSize; i++)
            key[i] = INT_MAX, minimaltree[i] = false;

        key[0] = 0;
        parent[0] = -1;

        for (int i = 0; i < matrixSize - 1; i++){
            int k = min(key, minimaltree);
            minimaltree[k] = true;
            for (int v = 0; v < matrixSize; v++)
                if (graph[k][v] && minimaltree[v] == false && graph[k][v] < key[v])
                    parent[v] = k, key[v] = graph[k][v];
        }
        show(parent, graph);
    }

};

int main(){
    Graph g;

    fstream input;
    input.open("graf.txt");
    int graph[matrixSize][matrixSize];
    static int size;
    input >> size;

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            input >> graph[i][j];

    g.prim_algorithm(graph);

    system("PAUSE");
    return 0;
}

