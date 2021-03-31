#include <iostream>
#include <cstring>

using namespace std;

enum Color {RED, BLACK};

struct node {
    int val;
    string skier;
    node* P;
    node* L;
    node* R;
    bool color;

    node(int value, string ski){
        this->val = value;
        this->skier=ski;
        L = R = P = NULL;
        this->color = RED;
    }

    bool isOnLeft() {
        return this == P->L;
    }

    node *Sibling() {
        if (P == NULL)
            return NULL;
        if (isOnLeft())
            return P->R;
        return P->L;
    }

    bool hasRedChild() {
        return (L != NULL && L->color == RED) || (R != NULL && R->color == RED);
    }
};

class RBT{

private:
    node *root;

protected:
    void LL(node *&, node *&); //rotacja w lewo
    void RR(node *&, node *&); //rotacja w prawo
    void fixRBT(node *&root, node *&A); //naprawa drzewa po dodaniu nowego wezla

public:
    RBT() {
        root = NULL;
    }
    void insert(int &, string);          //dodawanie
    void del(node *A);                   //usuwanie
    void bothBlackFix (node *A);         //funkcja pomocnicza przy usuwaniu
    void inorder();                      //wypisywanie
    node* search(int);                   //wyszukiwanie
};

void RBT::RR(node*& root, node *&A){
    A -> L = A -> L -> R;

    if(A->L != NULL)
        A->L->P=A;

    A->L->P=A->P;

    if (A->P == NULL)
        root=A->L;

    else if (A == A->P->L)
        A->P->L = A -> L;
    else
        A->P->R=A->L;

    A->L->R=A;
    A->P=A->L;
}

void RBT::LL(node *& root, node *& A) {
    A -> R = A -> R->L;

    if(A->R != NULL)
        A->R->P=A;

    A->R->P=A->P;

    if (A->P == NULL)
        root=A->R;
    else if (A == A->P->L)
        A->P->L = A -> R;
    else
        A->P->R=A->R;

    A->R->L=A;
    A->P=A->R;
}


node* insertNode(node* root, node *node){          // wstawianie wezla
    if (root == NULL)
        return node;
    if (node->val < root->val){
        root->L  = insertNode(root->L, node);
        root->L->P = root;
    }
    else if (node->val > root->val){
        root->R = insertNode(root->R, node);
        root->R->P = root;
    }
    return root;
}

void RBT::fixRBT(node *&root, node *&A){          // naprawa
    node *parentA = NULL;
    node *grandParentA = NULL;

    while ((A != root) && (A->color != BLACK) &&
           (A->P->color == RED)){
        parentA = A->P;
        grandParentA = A->P->P;
        if (A->P == grandParentA->L){
            node *uncleA = grandParentA->R;

            if (uncleA != NULL && uncleA->color == RED){
                grandParentA->color = RED;
                parentA->color = BLACK;
                uncleA->color = BLACK;
                A = grandParentA;
            }
            else{
                if (A == parentA->R){
                    LL(root, parentA);
                    A = parentA;
                    parentA = A->P;
                }
                RR(root, grandParentA);
                swap(parentA->color, grandParentA->color);
                A = parentA;
            }
        }
        else{
            node *uncleA = grandParentA->L;
            if ((uncleA != NULL) && (uncleA->color == RED)){
                grandParentA->color = RED;
                parentA->color = BLACK;
                uncleA->color = BLACK;
                A = grandParentA;
            }
            else{
                if (A == parentA->L){
                    RR(root, parentA);
                    A = parentA;
                    parentA = A->P;
                }
                LL(root, grandParentA);
                swap(parentA->color, grandParentA->color);
                A = parentA;
            }
        }
    }
    root->color = BLACK;
}


void RBT::insert(int &score, string name){    //wstawianie juz z nazwiskiem
    node *newNode = new node(score, name);
    root = insertNode(root, newNode);
    fixRBT(root, newNode);
}


node *successor(node *A) {   //nastepnik
    node *temp = A;
    while (temp->L != NULL)
        temp = temp->L;
    return temp;
}

node *replace(node *A) {
    if (A->L != NULL && A->R != NULL)
        return successor(A->R);

    if (A->L == NULL && A->R == NULL)
        return NULL;

    if (A->L != NULL)
        return A->L;
    else
        return A->R;
}

void RBT::bothBlackFix(node *A) {
    if (A == root)
        return;
    node *sibling = A->Sibling(), *parent = A->P;

    if (sibling == NULL)
        bothBlackFix(parent);
    else {
        if (sibling->color == RED) {
            parent->color = RED;
            sibling->color = BLACK;
            if (sibling->isOnLeft())
                RR(root, parent);
            else
                LL(root, parent);
            bothBlackFix(A);
        } else {
            if (sibling->hasRedChild()) {
                if (sibling->L != NULL && sibling->L->color == RED) {
                    if (sibling->isOnLeft()) {
                        sibling->L->color = sibling->color;
                        sibling->color = parent->color;
                        RR(root, parent);
                    } else {
                        sibling->L->color = parent->color;
                        RR(root, sibling);
                        LL(root, parent);
                    }
                } else {
                    if (sibling->isOnLeft()) {
                        sibling->R->color = parent->color;
                        LL(root, sibling);
                        RR(root, parent);
                    } else {
                        sibling->R->color = sibling->color;
                        sibling->color = parent->color;
                        LL(root, parent);
                    }
                }
                parent->color = BLACK;
            } else {
                sibling->color = RED;
                if (parent->color == BLACK)
                    bothBlackFix(parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}

void RBT::del(node *A) {
    node *B = replace(A);

    bool bothBlack = ((B == NULL || B->color == BLACK) && (A->color == BLACK));
    node *parent = A->P;

    if (A->L == NULL || A->R == NULL) {
        if (A == root) {
            A->val = B->val;
            A->L = A->R = NULL;
            delete B;
        } else {
            if (A->isOnLeft()) {
                parent->L = B;
            } else {
                parent->R = B;
            }
            delete A;
            B->P = parent;
            if (bothBlack) {
                bothBlackFix(B);
            } else {
                B->color = BLACK;
            }
        }
        return;
    }
    int temp;
    temp = B->val;
    B->val = A->val;
    A->val = temp;
    del(B);
}

void inorder(node* root) {
    if (root) {
        inorder(root->L);
        cout << root->val << "m " << root->skier <<endl;
        inorder(root->R);
    }
}

void RBT::inorder() {
    ::inorder(root);
}

node* search(node*& root, int score){
    while( root && root->val != score )
        root = ( score < root->val ) ? root->L: root->R;
    cout << root->skier << " wynik: "<< root->val;
    return root;
}

node* RBT::search(int score) {
    return ::search(root, score);
}

int main() {
    RBT tree;
    node *root = NULL;

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
        tree.insert(wynik, who);
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
            tree.del(search(root,score));
            cout << "Enter a new score: ";
            cin >> new_score;
            cout<< "Enter the player: ";
            cin >> player;
            tree.insert(new_score,player);
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