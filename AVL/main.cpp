//1.Zaprojektuj i zaimplemetuj strukturę danych dla przechowywwania wyników podczas zawodów narciarskich newnode oparciu o drzewo AVL.
//	Zawodnicy startują po kolei z odstępem 30 sec, po przejściu checkpointa wynik jest dodawany do struktury.Dodaj funkcje umożliwiające :
//		a.Wypisanie wszystkich wyników po kolei 
//		b.Dodanie nowego wyniku 
//		c.Wyszukiwania wyniku danego zawodnika oraz zmiany tego wyniku 

#include <iostream>
#include <string.h>
using namespace std;

struct node {
    int val;            // wartosc, wynik
    int balance;       // balans
    string skier;     // zawodnik
    node* L;         // lewy syn
    node* R;        // prawy syn
    node* P;       // rodzic
};

void RR(node*& root, node *A){
    node* B;
    node* temp;
    B = A->R;
    temp = A->P;
    A->R = B->L;

    if (A->R)
        A->R->P = A;

    B->L = A;
    B->P = temp;
    A->P = B;

    if (temp){
        if (temp->L == A)
            temp->L = B;
        else
            temp->R = B;
    }
    else
        root=B;

    if (B->balance == -1){
        A->balance = 0;
        B->balance = 0;
    }
    else{
        A->balance = -1;
        B->balance = 1;
    }
}

void LL(node*& root, node *A){
    node* B;
    node* temp;
    B = A->L;
    temp = A->P;
    A->L = B->R;

    if (A->L)
        A->L->P = A;

    B->R = A;
    B->P = temp;
    A->P = B;

    if (temp) {
        if (temp->L == A)
            temp->L = B;
        else
            temp->R = B;
    }
    else
        root=B;

    if (B->balance == 1){
        A->balance = 0;
        B->balance = 0;
    }
    else{
        A->balance = 1;
        B->balance = -1;
    }
}

void RL(node*& root, node *A){
    node* B=A->R;
    node* C=B->L;
    node* temp=A->P;
    B -> L = C -> R;
    if (B->L)
        B->L->P = B;
    A -> R = C -> L;
    if (A->R)
        A->R->P = A;
    C->L = A;
    C->R = B;
    A->P = B->P=C;
    C->P = temp;
    if (temp) {
        if (temp->L == A)
            temp->L = C;
        else
            temp->R = C;}
    else root=C;
    if (C->balance == -1)
        A->balance = 1;
    else
        A->balance = 0;

    if (C->balance == 1)
        B->balance = -1;
    else
        B->balance = 0;
        C->balance=0;
}

void LR(node*& root, node *A){
    node* B=A->L;
    node* C=B->R;
    node* temp=A->P;
    B -> R = C -> L;
    if (B->R)
        B->R->P = B;
    A -> L = C -> R;
    if (A->L)
        A->L->P = A;
    C->R = A;
    C->L = B;
    A->P = B->P=C;
    C->P = temp;
    if (temp) {
        if (temp->L == A)
            temp->L = C;
        else
            temp->R = C; }
    else root=C;
    if (C->balance == 1)
        A->balance = -1;
    else
        A->balance = 0;

    if (C->balance == -1)
        B->balance = 1;
    else
        B->balance = 0;
        C->balance=0;
}

void insert(node*& root, int x, string ski) {
    node *newnode, *pom, *pom2;
    newnode = new node;
    newnode->val = x;   //nowy wynik
    newnode->skier = ski;    //nowy zawodnik
    newnode->L = newnode->R = newnode->P = NULL;
    newnode->balance = 0;
    bool t;
    pom = root;

    //faza1
    if (!pom)
        root = newnode;
    else {
        while (1)
            if (x < pom->val) {
                if (!pom->L) {
                    pom->L = newnode;
                    break;
                } else pom = pom->L;
            } else {
                if (!pom->R) {
                    pom->R = newnode;
                    break;
                } else pom = pom->R;
            }
        newnode->P = pom;

        //faza2 - rownowaga

        if (pom->balance)
            pom->balance = 0;
        else {
            if (pom->L == newnode)
                pom->balance = 1;
            else
                pom->balance = -1;
            pom2 = pom->P;
            t = false;

            while (pom2) {
                if (pom2->balance) {
                    t = true;
                    break;
                };

                if (pom2->L == pom)
                    pom2->balance = 1;
                else
                    pom2->balance = -1;

                pom = pom2;
                pom2 = pom2->P;
            }

            if (t)
            {
                if (pom2->balance == 1) {
                    if (pom2->R == pom)
                        pom2->balance = 0;
                    else if (pom->balance == -1)
                        LR(root, pom2);
                    else
                        LL(root, pom2);
                } else {
                    if (pom2->L == pom)
                        pom2->balance = 0;
                    else if (pom->balance == 1)
                        RL(root, pom2);
                    else
                        RR(root, pom2);
                }
            }
        }
    }
}

void inorder(node* root) {    //wyswietlanie wszystkich wynikow
    if (root) {
        inorder(root->L);
        cout << root->val << "m " << root->skier <<endl;
        inorder(root->R);
    }
}

//wyszukiwanie:
node* search(node*& root, int x){   //x - wprowadzony wynik + pokazanie konkretu
    while( root && root->val != x )
        root = ( x < root->val ) ? root->L: root->R;
        cout << root->skier << " wynik: "<< root->val;
    return root;
}
node* search_2(node*& root, int x){   //x - wprowadzony wynik
    while( root && root->val != x )
        root = ( x < root->val ) ? root->L: root->R;
    return root;
}
//poprzednik
node* predecessor (node * pom ){
    node * pom2;
    if( pom )
    {
        if( pom->L ){
            pom = pom->L;
            while( pom->R )
                pom = pom->R;
        }else
            do{
                pom2 = pom;
                pom = pom->P;
            }
            while( pom && pom->R != pom2);
    }
    return pom;
}

node * remove_one ( node * & root, node * x )
{
    node  *a, *b, *c;
    bool helper;

    if(x->L && x->R)
    {
        b = remove_one(root, predecessor (x) );
        helper = false;
    }
    else
    {
        if(x->L)
        {
            b = x->L;
            x->L = NULL;
        }
        else
        {
            b = x->R;
            x->R = NULL;
        }
        x->balance = 0;
        helper = true;
    }

    if(b)
    {
        b->P = x->P;
        b->L = x->L;
        if( b->L )
            b->L->P= b;
            b->R = x->R;
        if(b->R)
            b->R->P = b;
        b->balance=x->balance;
    }

    if( x->P )
    {
        if( x->P->L == x )
            x->P->L = b;
        else
            x->P->R = b;
    }
    else
        root = b;

    if( helper )
    {
        c = b;
        b = x->P;
        while( b )
        {
            if( !b->balance )
            {
                if(b->L == c )
                    b->balance = -1;
                else
                    b->balance = 1;
                break;
            }
            else
            {
                if(((b->balance == 1 ) && (b->L == c ) ) || ((b->balance == -1 ) && (b->R == c ) ) )
                {
                    b->balance = 0;
                    c = b;
                    b = b->P;
                }
                else
                {
                    if(b->L == c )
                        a = b->R;
                    else
                        a = b->L;
                    if( !a->balance )
                    {
                        if(b->balance == 1 )
                            LL (root, b );
                        else
                            RR (root, b );
                        break;
                    }
                    else if(b->balance == a->balance )
                    {
                        if(b->balance == 1 )
                            LL (root, b );
                        else
                            RR (root, b );
                        c = a;
                        b = a->P;
                    }
                    else
                    {
                        if(b->balance == 1 )
                            LR (root, b );
                        else
                            RL (root, b );
                        c = b->P;
                        b = c->P;
                    }
                }
            }
        }
    }
    return x;
}


int main() {
    node *root = NULL;
    insert(root,50,"ja");
    insert(root,70,"Ola");

    menu:
    cout << "What you want to do: " << endl;
    cout << "Add a new score - click 1" << endl;
    cout << "See the scores one by one - click 2" << endl;
    cout << "Search for a player - click 3" << endl;
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
        string answer;
        int score;
        int new_score;
        string player;
        cout << "Searching" << endl << "Enter wanted score: ";
        cin>>score;
        search(root, score);
        cout << endl;
        cout << "Do you want to change the score? ";
        cin >> answer;
        if (answer == "yes") {
            remove_one(root,search_2(root,score));
            cout << "Enter a new score: ";
            cin >> new_score;
            cout<< "Enter the player: ";
            cin >> player;
            insert(root,new_score,player);
            inorder(root);
            goto menu;
        }
        else
            goto menu;
    }
    else if (choice == 0) {  //koniec
        exit(0);
    }
}
