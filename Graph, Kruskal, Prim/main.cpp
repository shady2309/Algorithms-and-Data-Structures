//kruskal
#include <iostream>
#include <fstream>

using namespace std;

string city[9] = {"Butynga", "Klajpeda", "Taurogi",
                  "Szawle", "Poniewiez", "Uciana",
                  "Kowno", "Mariampol", "Wilno"};
class Graph {
public:
    struct node
    {
        node* next;
        int start;
        int aim;
        int cost;
    };

    void add(node*& H, int from, int destination, int cost) {
        node* p = new node;
        p->start = from;
        p->aim = destination;
        p->cost = cost;
        p->next = H;
        H = p;
    }

    void addSort(node*& H, int start, int aim, int cost) {
        if (H == NULL)
            add(H, start, aim, cost);
        else{
            node* p = H;
            if (H->cost > cost)
                add(H, start, aim, cost);
            else{
                while (p->next && p->next->cost < cost)
                    p = p->next;
                add(p->next, start, aim, cost);
            }
        }
    }

    static void show(node* S) {
        node* p = S;
        while (p != NULL) {
            for(int i=0; i < sizeof(city); i++) {
                if (p->aim == i)
                    cout << city[i]<<"("<<p->cost<<")"<< "---> ";
            }
            p = p->next;
        }
        cout << "Finish" << endl;
    }


    void kruskal_algorithm(node*& neighbors, int size){
        int cost = 0;
        int help = 1;
        int* tree = new int[size];
        for (int i = 0; i < size; i++)
            tree[i] = 0;
        node* p = new node;
        p = NULL;
        int** color = new int* [size];        //0 - nieodwiedzone
        for (int i = 0; i < size; i++) {
            color[i] = new int[size];
            for (int j = 0; j < size; j++)
                color[i][j] = 0;
        }
        while (neighbors) {
            if (!(color[neighbors->aim][neighbors->start] && color[neighbors->start][neighbors->aim])) {
                if (tree[neighbors->start] == 0 && tree[neighbors->aim] == 0) {
                    tree[neighbors->start] = help;
                    tree[neighbors->aim] = help;
                    color[neighbors->aim][neighbors->start] = 1;
                    color[neighbors->start][neighbors->aim] = 1;
                    add(p, neighbors->start, neighbors->aim, neighbors->cost);
                    cost += neighbors->cost;
                    help++;
                }
                else if (tree[neighbors->start] == 0 && tree[neighbors->aim] != 0) {
                    tree[neighbors->start] = tree[neighbors->aim];
                    color[neighbors->aim][neighbors->start] = 1;
                    color[neighbors->start][neighbors->aim] = 1;
                    add(p, neighbors->start, neighbors->aim, neighbors->cost);
                    cost += neighbors->cost;

                }
                else if (tree[neighbors->aim] == 0 && tree[neighbors->start] != 0) {
                    tree[neighbors->aim] = tree[neighbors->start];
                    color[neighbors->aim][neighbors->start] = 1;
                    color[neighbors->start][neighbors->aim] = 1;
                    add(p, neighbors->start, neighbors->aim, neighbors->cost);
                    cost += neighbors->cost;
                }
                else if (tree[neighbors->start] == tree[neighbors->aim]) {
                }
                else if (tree[neighbors->start] != tree[neighbors->aim]) {
                    int a = tree[neighbors->start];
                    int b = tree[neighbors->aim];
                    for (int i = 0; i < size; i++) {

                        if (tree[i] == a || tree[i] == b)
                            tree[i] = help;
                    }
                    color[neighbors->aim][neighbors->start] = 1;
                    color[neighbors->start][neighbors->aim] = 1;
                    add(p, neighbors->start, neighbors->aim, neighbors->cost);
                    cost += neighbors->cost;
                    help++;
                }
            }
            neighbors = neighbors->next;

        }
        cout << endl << "Entire route " << cost << endl;
        while (p) {
            for(int i=0; i < sizeof(city); i++) {
                if (p->start == i)
                    cout << city[i];
            }
            for(int i=0; i < sizeof(city); i++) {
                if (p->aim == i)
                    cout << " -> " << city[i] << " (" << p->cost << ")" << endl;
            }
            p = p->next;
        }
    }

};

int main(){
    Graph g;
    fstream input;
    input.open("graf.txt");
    static int size;
    input >> size;
    int start, aim, cost;

    Graph::node* neighbors = new Graph::node;
    neighbors = NULL;

    for (int j = 0; j < size; j++) {
        start = j;
        for (int i = 0; i < size; i++) {
            aim = i;
            input >> cost;
            if (cost) {
                g.addSort(neighbors, start, aim, cost);
            }
        }
    }
    g.show(neighbors);
    g.kruskal_algorithm(neighbors, size);
    system("PAUSE");
    return 0;
}
