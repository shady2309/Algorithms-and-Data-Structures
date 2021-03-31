#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>
#include <sstream>
#include <iomanip>

using namespace std;

int KRhash(string w, int w_size,int pos){
    int i, h;
    h = 0;

    for (i = pos; i < w_size+pos; i++)
        h = 26 * h + (w[i] - 97);
    h = h % 23;
    return h;
}

int naiveSearch(string s, string w){
    bool found = false;
    for (int i = 0; i < s.length(); i++){
        found = true;
        for (int j = 0; j < w.length(); j++){
            if (s[j + i] != w[j]){
                found = false;
                break;
            }
        }
        if (found){
            return i;
        }
    }
    return -1;
}

int KnuttMorrisPratt(string s, string w){
    int* PI;
    PI = new int[w.length()];

    for (int i = 0; i < w.length(); i++)
        PI[i] = 0;

    int b = -1;
    PI[0] = -1;


    for (int i = 1; i < w.length(); i++){
        while ((b > -1) && w[b] != w[i - 1]) b = PI[b];
        ++b;
        if (i == w.length() || (w[i] != w[b])) PI[i] = b;
        else PI[i] = PI[b];
    }

    int pos = 0;
    b = 0;

    for (int i = 0; i < s.length(); i++){
        while ((b > -1) && (w[b] != s[i])) b = PI[b];
        if (++b == w.length()){
            while (pos < i - b + 1)
                pos++;
            b = PI[b];
        }
    }

    return pos;
}

int KarpRabin(string s, string w){
    int pos = 0;
    int i = 0;
    int hw = KRhash(w, w.length(),0);
    int hs = KRhash(s, w.length(),0);

    while (1){
        if ((hw == hs) && w == s.substr(i, w.length()))
            return i;
        i++;
        if (i == s.length() - w.length())
            break;
        hs = KRhash(s, w.length(), i);
    }
    return -1;
}

void search(string word){
    ifstream file;
    string line;
    file.open("Job-case1.inp");
    if (file.good()) {
        while (getline(file, line)) {
            regex e(word);
            bool match = regex_search(line, e);
            if (match) {
                vector<string> word;
                int x = naiveSearch(line, "=");
                if (x != -1) {
                    string s = "";
                    for (int i = x + 1; i < line.size(); i++) {
                        s=s+line[i];
                        int x2 = naiveSearch(s, ", ");
                        if(x2 == -1)
                            cout << line[i];
                    }
                    cout << "  ";
                }
            }
        }
        cout << endl;
    }
    file.close();
}

vector<string> split(string str, char delimiter) {
    vector<string> vect;
    stringstream stri(str);
    string y;

    while(getline(stri, y, delimiter)) {
        vect.push_back(y);
    }
    return vect;
}

void searchMaterials(string word){
    vector<string> name;
    vector<string> conductivityM;
    vector<string> densityM;
    vector<string> specificHeat;
    string s = "";
    ifstream file;
    string line;
    string conductivity;
    string density;
    string specific_heat;
    file.open("Job-case1.inp");
    if (file.good()) {
        while (getline(file, line)) {
            regex e(word);
            bool match = regex_search(line, e);
            if (match) {
                vector<string> word;
                int x = naiveSearch(line, "=");
                if (x != -1) {
                    for (int i = x + 1; i < line.size(); i++) {
                        s = s+ line[i];
                    }
                    s = s + " ";
                    getline(file,line);
                    getline(file,line);
                    conductivity = conductivity + line;

                    getline(file,line);
                    getline(file,line);
                    density = density + line;

                    getline(file,line);
                    getline(file,line);
                    specific_heat = specific_heat + line;
                }
            }
        }
    }
    conductivityM = split(conductivity, ',');

    densityM = split(density, ',');

    specificHeat = split(specific_heat, ',');

    name = split(s, ' ');

    cout<<endl;
    cout<< setw(20) << "Name: " << setw(20) << "   Conductivity: " <<
            setw(20) << "   Density: " << setw(20) << "   Specific heat: " << endl;
    for(int i=0;i<name.size();i++) {
        cout << setw(20) << name[i] << setw(20) << conductivityM[i] << setw(20) << densityM[i] << setw(20) << specificHeat[i] << endl;
    }
    file.close();
}

void checkStep(string word){
    bool interactionsF, outputRequestsF, fieldOutputF, historyF, endF = false;
    int numberL =0;
    int sline, interactionsL, outputRequestsL, fieldOutputL, historyL, endL;
    ifstream file;
    string line;
    file.open("Job-case1.inp");
    if (file.good()) {
        while (getline(file, line)) {
            numberL++;
            regex e(word); // the pattern
            bool good = regex_search(line, e);
            if (good) {
                vector<string> word;
                int x = naiveSearch(line, ":");
                if (x != -1) {
                    string s = "";
                    for (int i = x + 1; i < line.size(); i++) {
                        s=s+line[i];
                    }
                    sline = numberL;
                    cout<<"Find "<<s<<" Line "<<sline<<endl;
                }
            }
            string inter = "INTERACTIONS";
            int posinter = naiveSearch(line, inter);
            if (posinter!=-1) {
                interactionsF = true;
                interactionsL=numberL;
            }
            string outp = "OUTPUT REQUESTS";
            int posoutp = naiveSearch(line, outp);
            if (posoutp!=-1){
                outputRequestsF = true;
                outputRequestsL=numberL;
            }

            string fiel = "FIELD OUTPUT";
            int posfiel = naiveSearch(line, fiel);
            if (posfiel!=-1){
                fieldOutputF = true;
                fieldOutputL=numberL;
            }

            string his = "HISTORY OUTPUT";
            int poshis = naiveSearch(line, his);
            if (poshis!=-1){
                historyF = true;
                historyL=numberL;
            }

            string end = "End Step";
            int posend = naiveSearch(line, end);
            if (posend!=-1){
                endF = true;
                endL=numberL;
            }
        }
    }
    if(interactionsF && outputRequestsF && fieldOutputF && historyF && endF &&
       (interactionsL < endL && interactionsL > sline) && (outputRequestsL < endL && outputRequestsL > sline) && (fieldOutputL < endL && fieldOutputL > sline)
       && (historyL < endL && historyL > sline))
        cout<<"Correct definition of the steppe"<<endl;
    else
        cout<<"Incorrect definition of the steppe"<<endl;

    file.close();
}

int main(){
    clock_t t;
    t = clock();
    cout<<endl;

    string parts = "Part, name=";
    cout << "Parts: ";
    search(parts);
    cout<<endl;

    string elsets = "Elset, elset=";
    cout << "Elsets: ";
    search(elsets);
    cout<<endl;

    string nsets = "Nset, nset=";
    cout << "Nsets: ";
    search(nsets);
    cout<<endl;

    string elements = "Element, type=";
    cout << "Elements: ";
    search(elements);
    cout<<endl;

    string materials = "Material, name=";
    cout << "Materials: ";
    searchMaterials(materials);
    cout<<endl;

    string step = "STEP:";
    checkStep(step);
    cout<<endl;

    t = clock() - t;
    cout << "Program execution time: "<< (float)t / CLOCKS_PER_SEC <<endl;

    system("pause");
}