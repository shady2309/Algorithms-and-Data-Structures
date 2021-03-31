#include <iostream>
#include <fstream>

#define WHITE 'W'
#define GREY 'G'
#define BLACK 'B'
#define FULL 'F'

using namespace std;

string city[9] = {"Butynga", "Klajpeda", "Taurogi",
                  "Szawle", "Poniewiez", "Uciana",
                  "Kowno", "Mariampol", "Wilno"};

fstream file;

class Graph {
public:
    struct node {
        int aim;
        int cost;
        node* next;
    };

private:
    int size;
    node**LS;				
    char *colors;
    int *predecessors;
    int *costs;

public:

    void add(node*&H, int aim, int cost) {
        node* added = new node;
        added->aim = aim;
        added->cost = cost;
        added->next = H;
        H = added;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            node *p = LS[i];
            cout << "[" << city[i] << "]-> ";
            while (p != NULL) {
                for (int i = 0; i < sizeof(city); i++) {
                    if (p->aim == i)
                        cout << city[i] << " (" << p->cost << ")" << "-> ";
                }
                p = p->next;
            }
            cout << "KONIEC" << endl;
        }
    }

    void fileRead() {
        int help;
        for (int w = 0; w < size; w++) {
            for (int k = 0; k < size; k++) {
                file >> help;
                if (help != 0) {
                    add(LS[w], k, help);
                }
            }
        }
    }

    Graph() {
        file.open("graf.txt");
        file >> size;
        LS = new node*[size];
        for (int i = 0; i < size; i++) {
            LS[i] = NULL;
        }
        colors = new char[size];
        predecessors = new int[size];
        costs = new int[size];
    }


    void Dijkstra(int start) {
        node*p = NULL;
        int j, k;

        for (int i = 0; i < size; i++) {				                   //wartosci tablic
            colors[i] = WHITE;
            predecessors[i] = -1;
            costs[i] = -1;
        }
        colors[start] = GREY;							                   //wartosci tablic dla wierzcholka startowego
        predecessors[start] = -1;
        costs[start] = 0;

        int cost, l;

        while (true) {
            l = 0;
            while(l < size && colors[l] != GREY)			               //odleglosci do obojetnie ktorego wezla szarego
                l++;								    	               //zeby moc do czegos porownac w nastepnej petli

            cost = costs[l];
            char cols = BLACK;

            for (int m = 0; m < size; m++) {
                if (colors[m] == GREY && costs[m] <= cost) {			   //szukam wezla szarego o najmniejszej odleglosci od startu
                    cost = costs[m];
                    j = m;
                }
                if (colors[m] != BLACK)									   //gdy cala tablica kolorow jest czarna
                    cols = FULL;									   	   //koncze algorytm dlatego ustawiam znacznik
            }
            if (cols == BLACK)										   	   //WARUNEK KONCA ALGORYTMU
                break;

            p = LS[j];
            while (p != NULL) {
                k = p->aim;

                if (colors[k] != BLACK) {
                    if (colors[k] == GREY) {							   //gdy kolor wezla jest szary sprawdzam odleglosci
                        if (costs[k] > (costs[j] + p->cost)) {
                            costs[k] = costs[j] + p->cost;
                            predecessors[k] = j;
                        }
                    }
                    else {		                                           //gdy kolor wezla jest bialy nie musze sprawdzac odlegosci bo jest on rozpatrywany po raz pierwszy
                        costs[k] = costs[j] + p->cost;
                        predecessors[k] = j;
                    }
                    colors[k] = GREY;
                }
                p = p->next;
            }
            colors[j] = BLACK;
        }
    }

    void show(int x) {
        cout << city[x];
        if (predecessors[x] != -1) {
            cout << "->";
            show(predecessors[x]);
        }
        else
            cout << endl;
    }


    void effect() {
        cout<<"Calkowite koszta: "<<endl;
        for (int i = 0; i < size; i++)
            cout << "[" << city[i] << "]=" << costs[i] << endl;
        cout<<endl<<"Kolory: "<<endl;
        for (int i = 0; i < size; i++)
            cout << "[" << city[i] << "]=" << colors[i] << endl;
        cout<<endl<<"Poprzednicy: "<<endl;
        for (int i = 0; i < size; i++)
            cout << "[" << city[i] << "]=" << predecessors[i] << endl;
        cout << endl;
    }
};

int main(){
    Graph g;
    g.fileRead();
    g.print();
    cout<<endl;
    g.Dijkstra(3);
    g.effect();
    for(int i=0; i<9; i++) {
        cout << "Droga z " << city[i] << ": ";
        g.show(i);
    }
    system("pause");
    return 0;


}