#include <iostream>

using namespace std;

string city[9] = {"Butynga", "Klajpeda", "Taurogi", "Szawle", "Poniewiez", "Uciana", "Kowno", "Mariampol", "Wilno"};

struct Edge {
    int start;
    int aim;
    int cost;
};

struct Graph {
    int V;
    int E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

void show(int *cost, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if(cost[i] < 9999)
            cout << city[i] << ": " << cost[i] << endl;
        else
            cout << city[i] << ": " << "brak polaczenia" << endl;
    }
}

void BellmanFord(struct Graph* graph, int start) {
    int V = graph->V;
    int E = graph->E;
    int distance[V];
    for (int i = 0; i < V; i++)
        distance[i] = 9999;
    distance[start] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int from = graph->edge[j].start;
            int destination = graph->edge[j].aim;
            int cost = graph->edge[j].cost;
            if (distance[from] != 9999 && (distance[from] + cost) < distance[destination])
                distance[destination] = distance[from] + cost;
        }
    }

    //znajdowanie cyklu ujemnego
    for (int i = 0; i < E; i++) {
        int from = graph->edge[i].start;
        int destination = graph->edge[i].aim;
        int cost = graph->edge[i].cost;
        if (distance[from] != 9999 && (distance[from] + cost) < distance[destination]) {
            cout<<"Graph contains negative cycle"<<endl;
        }
    }
    show(distance, V);
}

int main() {
    int V = 9;
    int E = 24;
    struct Graph* graph = createGraph(V, E);

    //edge butynga --> klajpeda
    graph->edge[0].start = 0;
    graph->edge[0].aim = 1;
    graph->edge[0].cost = 43;

    //edge butynga --> szawle
    graph->edge[1].start = 0;
    graph->edge[1].aim = 3;
    graph->edge[1].cost = 148;

    //edge klajpeda --> butynga
    graph->edge[2].start = 1;
    graph->edge[2].aim = 0;
    graph->edge[2].cost = 43;

    //edge klajpeda --> szawle
    graph->edge[2].start = 1;
    graph->edge[2].aim = 3;
    graph->edge[2].cost = 155;

    //edge klajpeda --> taurogi
    graph->edge[2].start = 1;
    graph->edge[2].aim = 2;
    graph->edge[2].cost = 100;

    //edge taurogi --> klajpeda
    graph->edge[3].start = 2;
    graph->edge[3].aim = 1;
    graph->edge[3].cost = 100;

    //edge taurogi --> szawle
    graph->edge[3].start = 2;
    graph->edge[3].aim = 3;
    graph->edge[3].cost = 102;

    //edge szawle --> butynga
    graph->edge[4].start = 3;
    graph->edge[4].aim = 0;
    graph->edge[4].cost = 148;

    //edge szawle --> klajpeda
    graph->edge[4].start = 3;
    graph->edge[4].aim = 1;
    graph->edge[4].cost = 155;

    //edge szawle --> taurogi
    graph->edge[4].start = 3;
    graph->edge[4].aim = 2;
    graph->edge[4].cost = 102;

    //edge szawle --> poniewiez
    graph->edge[4].start = 3;
    graph->edge[4].aim = 4;
    graph->edge[4].cost = 80;

    //szawle --> kowno
    graph->edge[4].start = 3;
    graph->edge[4].aim = 6;
    graph->edge[4].cost = 145;

    //poniewiez --> szawle
    graph->edge[5].start = 4;
    graph->edge[5].aim = 3;
    graph->edge[5].cost = 80;

    //poniewiez --> uciana
    graph->edge[5].start = 4;
    graph->edge[5].aim = 5;
    graph->edge[5].cost = 93;

    //edge uciana --> poniewiez
    graph->edge[6].start = 5;
    graph->edge[6].aim = 4;
    graph->edge[6].cost = 93;

    //edge uciana --> wilno
    graph->edge[6].start = 5;
    graph->edge[6].aim = 8;
    graph->edge[6].cost = 97;

    //edge kowno --> szawle
    graph->edge[7].start = 6;
    graph->edge[7].aim = 3;
    graph->edge[7].cost = 145;

    //edge kowno --> mariampol
    graph->edge[7].start = 6;
    graph->edge[7].aim = 7;
    graph->edge[7].cost = 57;

    //edge kowno --> wilno
    graph->edge[7].start = 6;
    graph->edge[7].aim = 8;
    graph->edge[7].cost = 110;

    //edge mariampol --> kowno
    graph->edge[8].start = 7;
    graph->edge[8].aim = 6;
    graph->edge[8].cost = 57;

    //edge mariampol --> wilno
    graph->edge[8].start = 7;
    graph->edge[8].aim = 8;
    graph->edge[8].cost = 136;

    //edge wilno --> kowno
    graph->edge[9].start = 8;
    graph->edge[9].aim = 6;
    graph->edge[9].cost = 110;

    //edge wilno --> uciana
    graph->edge[9].start = 8;
    graph->edge[9].aim = 5;
    graph->edge[9].cost = 97;

    //edge wilno --> mariampol
    graph->edge[9].start = 8;
    graph->edge[9].aim = 7;
    graph->edge[9].cost = 136;

    int start =0;

    cout << "Calkowity koszt " << city[start] << " do: " << endl;

    BellmanFord(graph, start);

    return 0;
}