#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int modulo(int a, int b)
{
    int res = a - ((a / b) * b);
    return res + (res < 0) * b;
}

string cypher(string word, string alpha, int key)
{
    string cyphered;
    for (string::iterator i = word.begin(); i != word.end(); i++)
    {
        cyphered.push_back(alpha[modulo(alpha.find(*i) + key, alpha.length())]);
    }
    return cyphered;
}

void menu(int narg, char *args[])
{
    switch(narg) {
        case 2:
           ifstream file;
           file.open(args[1]);
           if (file.is_open()) 
           {
               file.seekg(0, ios::end);
               string fullWord;
               fullWord.reserve(file.tellg());
               file.seekg(0, ios::beg);
               fullWord.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

               int uKey;
               string uAlpha; 
               cout << "Ingrese la clave con la que se cifrara: ";
               cin >> uKey;
               cout << "Ingrese el alfabeto a ser usado, pulse enter para usar el alfabeto por defecto (abcdefghijklmnopqrstuvwxyz ): ";
               cin.get();
               getline(cin, uAlpha);

               if (uAlpha.empty()) cout << cypher(fullWord, "abcdefghijklmnopqrstuvwxyz ", uKey) << endl;
               else cout << cypher(fullWord, uAlpha, uKey) << endl;
           }
    }
}

int main(int argc, char *argv[])
{
    menu(argc, argv);
}
