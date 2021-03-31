//1.Zaprojektuj i zaimplemetuj strukturę danych dla przechowywwania wyników podczas zawodów narciarskich w oparciu o drzewo BST.
//	Zawodnicy startują po kolei z odstępem 30 sec, po przejściu checkpointa wynik jest dodawany do struktury.Dodaj funkcje umożliwiające :
//		a.Wypisanie wszystkich wyników po kolei 
//		b.Dodanie nowego wyniku 
//		c.Wyszukiwania wyniku danego zawodnika oraz zmiany tego wyniku 

#include <iostream>
#include <string.h>
using namespace std;

struct node {
    int val;           // wartosc, wynik
    string skier;     //zawodnik
    node* L;         // lewy syn
    node* R;        // prawy syn
    node* P;       // rodzic
};

void insert(node*& root, int x, string ski) {
    if (root == NULL) {							//jesli drzewo jest puste
        root = new node;
        root->val = x;
        root->skier=ski;
        root->L = root->R = root->P = NULL;
    }
    else {										//jesli drzewo nie jest puste
        if (x < root->val) {					//jesli wstawiana wartosci jest mniejsza od wartosci korzenia
            insert(root->L, x, ski);			//rekurencja na root->L
            root->L->P = root;					//ustawienie ojca
        }
        else {
            insert(root->R, x, ski);
            root->R->P = root;

        }
    }
}
void inorder(node* root) {
    if (root) {
        inorder(root->L);
        cout << root->val << "m " << root->skier <<endl;
        inorder(root->R);
    }
}


//wyszukiwanie:
node* search(node*& root, int x){
    if (root != NULL)
    {
        if (root->val==x) {
            cout<<root->skier;
            return root;
        }
        else if (x > root->val)
            search(root->R, x);
        else
            search(root->L, x);
    }
}
void search_and_change(node*& root, int score, int new_score){
    if (root != NULL)
    {
        if (root->val==score) {
            cout << "Changed " << root->skier << " score from " << root -> val << " to " << new_score<<"m"<<endl;
            root -> val=new_score;
        }
        else if (score > root->val)
            search_and_change(root->R, score,new_score);
        else
            search_and_change(root->L, score,new_score);
    }
}


int main() {
    node *root = NULL;
    menu:
    cout << "What you want to do: " << endl;
    cout << "Add a new score - click 1" << endl;
    cout << "See the scores one by one - click 2" << endl;
    cout << "Search for a player - click 3" << endl; //tam potem opcja zmiany wyniku
    cout << "Exit - click 0" << endl;

    int choice;
    cin >> choice;

    if (choice == 1) { //nowy wynik
        string who;
        int wynik;
            cout << "Enter the name of the player: ";
            cin >> who;
            cout << "Enter the score: ";
            cin >> wynik;
            insert(root, wynik, who);
        cout << endl;
        cout << endl;
        goto menu;
    }
    else if (choice == 2) {  //wyniki
        cout << "Scores" << endl;
        inorder(root);
        cout << endl;
        cout << endl;
        goto menu;

    }
    else if (choice == 3) { //wyszukiwanie
        string search_skier;
        string answer;
        int score;
        int new_score;
        cout << "Searching" << endl << "Enter wanted score: ";
//        cin >> search_skier;
cin>>score;
        search(root, score);
        cout << endl;
        cout << "Do you want to change the score? ";
        cin >> answer;
        if (answer == "yes") {
            cout << "Enter a new score: ";
            cin >> new_score;
            search_and_change(root,score,new_score);
            goto menu;
        }
            else
                goto menu;
    }
    else if (choice == 0) {  //koniec
        exit(0);
    }
}
