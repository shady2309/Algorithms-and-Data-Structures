//separate chaining
#include <iostream>
#include <ctime>
#include <random>
#include <string>


using namespace std;

int hash_table[1000];

struct node {
    node* next;
    int value;
};

node* hash_table_lists[1000];


void fillWithZeros()
{
    for (int i = 0; i < 1000; i++)
    {
        hash_table[i] = -1;
    }
}

int Gethash(int value)
{
    return value%sizeof(hash_table);
}

long long polynomialHashing(string const& string){
    int p = 31;
    int m = 1e9 + 9;
    long long pPower = 1;
    long long hashValue = 0;

    for (int i = 0; i < string.length(); i++) {
        hashValue = (hashValue + (string[i] - 'a' + 1) * pPower)% m;
        pPower = (pPower * p) % m;
    }
    return hashValue;
}

int findElement(int value){
    for(int i=0; i< sizeof(hash_table); i++){
        if(hash_table[Gethash(value)] == value)
            return Gethash(value);
        else
            return -1;
    }
}


node* findListElemnt(int value)
{
    node* pom;
    pom = hash_table_lists[Gethash(value)];

    while (pom != NULL)
    {
        if (pom->value == value)
            return pom;
        else pom = pom->next;
    }

    return NULL;
}

void addNewElement(int value)
{
    if (hash_table[Gethash(value)] == -1)
        hash_table[Gethash(value)] = value;
}

void addFront(node*& head, int value)
{
    node* nodeToAdd = new node;
    nodeToAdd->value = value;
    nodeToAdd->next = head;
    head = nodeToAdd;
}

void addNewListElement(int value)
{
    addFront(hash_table_lists[Gethash(value)], value);
}


string random_string(){
    string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    random_device rd;
    mt19937 generator(rd());

    shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32);    // 32 znaki
}

int main()
{
    fillWithZeros();

    clock_t start = clock();
    for(int i =0;i<100;i++) {
        addNewElement(polynomialHashing(random_string()));
    }
    addNewElement(polynomialHashing("dzieci z bullerbyn"));
    addNewElement(polynomialHashing("dziady"));
    addNewElement(polynomialHashing("pinokio"));
    addNewElement(polynomialHashing("w 80 dni dookola swiata"));
    addNewElement(polynomialHashing("hari pota"));
    addNewElement(polynomialHashing("pies ktory jezdzil koleja"));
    addNewElement(polynomialHashing("wladca pierscieni"));
    addNewElement(polynomialHashing("nedznicy"));
    addNewElement(polynomialHashing("edyp"));
    addNewElement(polynomialHashing("zbrodnia i kara"));
    addNewElement(polynomialHashing("ferdydurke"));
    addNewElement(polynomialHashing("krzyzacy"));


    findElement(polynomialHashing("pinokio"));
    cout<<"Czas wykonywania: "<<clock() - start<<" ms"<<endl;

    system("pause");
}