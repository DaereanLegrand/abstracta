#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <math.h>

using namespace std;

int modulo(int a, int b)
{
    int res = a - ((a / b) * b);
    return res + (res < 0) * b;
}

bool inVector(vector<pair<char, int>> myVec, pair<char, int> objective)
{
    for (pair<char, int> i: myVec)
        if (i == objective) return true;
    return false;
}

vector<pair<char, int>> getFrequencyInOrder(string message)
{
    unordered_map<char, int> dict;     
    for (char i: message)
        dict[i]++;

    vector<pair<char, int>> inOrder;
    for (pair<char, int> iter: dict)
    {
        pair<char, int> temp;
        for (pair<char, int> i: dict)
            if (i.second > temp.second && !inVector(inOrder, i)) temp = i;
        inOrder.push_back(temp);
    }

    return inOrder;
}

string decypher(string message, string alpha, int key)
{
    string decyphered;
    for (string::iterator i = message.begin(); i != message.end(); i++)
        decyphered.push_back(alpha[modulo(alpha.find(*i) - key, alpha.length())]);
    cout << decyphered << endl;
    return decyphered;
}

pair<int, string> getBestKey(string message, string alpha)
{
    string englishFrequency = " etaoinshrdlcumwfgypbvkjxqz";
    string vocales = "aeiou ";
    vector<pair<char, int>> inOrder = getFrequencyInOrder(message);
    int key = 0, points = 0, freqIndex = 0;
    string tempDec, decMes;

    for (pair<char, int> i: inOrder)
    {
        int newPoint = 0;
        int rest = modulo(alpha.find(i.first) - alpha.find(englishFrequency[freqIndex]), alpha.length());
        tempDec = decypher(message, alpha, rest);
        
        vector<pair<char, int>> tempFrec = getFrequencyInOrder(tempDec);        
        for (vector<pair<char, int>>::iterator j = tempFrec.begin(); j != tempFrec.end(); j++)
            newPoint += j->second * (pow(englishFrequency.length() - englishFrequency.find(j->first), 2));

        if (newPoint > points)
        {
            points = newPoint;
            key = rest;
            decMes = tempDec;
        }

        freqIndex++;
    }
    return pair<int, string>(key, decMes);
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

               string uAlpha; 
               cout << "Ingrese el alfabeto a ser usado, pulse enter para usar el alfabeto por defecto (abcdefghijklmnopqrstuvwxyz ): ";
               getline(cin, uAlpha);

               pair<int, string> keyAndMessage;
               if (uAlpha.empty()) keyAndMessage = getBestKey(fullWord, "abcdefghijklmnopqrstuvwxyz ");
               else keyAndMessage = getBestKey(fullWord, uAlpha);

               cout << "Clave: " << keyAndMessage.first << "\nMensaje: " << keyAndMessage.second << endl;
           }
    }
}

int main(int argc, char *argv[])
{
    menu(argc, argv);
}
