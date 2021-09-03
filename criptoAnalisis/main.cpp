#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void decypher(string word, string alpha)
{
    unordered_map<char, int> dict;     
    for (string::iterator i = word.begin(); i != word.end(); i++)
    {
        unordered_map<char, int>::iterator pos = dict.find(*i);
        if (pos == dict.end()) dict[*i] = 0; 
        dict[*i] += 1;
    }

    unordered_map<char, int>::iterator pivot = dict.begin();
    while (pivot != dict.end())
    {
        unordered_map<char, int>::iterator startPlus = pivot;
        startPlus++;
        for (unordered_map<char, int>::iterator comparer = pivot; startPlus != dict.end(); comparer++, startPlus++)
        {
            if (comparer->second < startPlus->second) comparer->swap(*startPlus);
        }
        pivot++;
    }


    for (unordered_map<char, int>::iterator i = dict.begin(); i != dict.end(); i++)
    {
        cout << i->first << " => " << i->second << endl;
    }

}

int main(int argc, char *argv[])
{
    string alpha = "abcdefghijklmnopqrstuvwxyz ";
    decypher("if he had anything confidential to say he wrote it in cipher that is by so changing the order of the letters of the alphabet that not a word could be made out", alpha);
    
}
