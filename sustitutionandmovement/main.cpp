#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

void charCounter(string word)
{
    string alpha = "abcdefghijklmnopqrstuvwxyz";

    for (string::iterator i = alpha.begin(); i != alpha.end(); i++)
    {
        int n = 0;
        for (string::iterator j = word.begin(); j != word.end(); j++)
        {
            if (*j == *i) n++;
        }
        cout << "Se encontro: " << *i << ",\t" << n << " veces." << std::endl;
    }
}

void wordReplacer(string word)
{
    while (true)
    {
        string input1, input2;
        cout << "Ingrese el caracter a ser reemplazado: ";
        cin >> input1;
        cout << "Ingrese el caracter con el que se reemplazara: ";
        cin >> input2;

        while (word.find(input1) != string::npos)
        {
            word[word.find(input1)] = toupper(input2[0]); 
        }
        cout << word << std::endl;
        cout << "Desea continuar?";
        cin >> input1;
        cout << std::endl;

        if (input1 == "n" || input1 == "N") break;
    }
    
}

int main()
{
   // string wordEnc = "lrvmnir bpr sumvbwvr jx bpr lmiwv yjeryrkbi jx qmbm wi bpr xjvni mkd ymibrut jx irhx wi bpr riirkvr jx ymbinlmtmipw utn qmumbr dj w ipmhh but bj rhnvwdmbr bpr yjeryrkbi jx bpr qmbm mvvjudwko bj yt wkbrusurbmbwjk lmird jk xjubt trmui jx ibndt wb wi kjb mk rmit bmiq bj rashmwk rmvp yjeryrkb mkd wbi iwokwxwvmkvr mkd ijyr ynib urymwk nkrashmwkrd bj ower m vjyshrbr rashmkmbwjk jkr cjnhd pmer bj lr fnmhwxwrd mkd wkiswurd bj invp mk rabrkb bpmb pr vjnhd urmvp bpr ibmbr jx rkhwopbrkrd ywkd vmsmlhr jx urvjokwgwko ijnkdhrii ijnkd mkd ipmsrhrii ipmsr w dj kjb drry ytirhx bpr xwkmh mnbpjuwbt lnb yt rasruwrkvr cwbp qmbm pmi hrxb kj djnlb bpmb bpr xjhhjcwko";

    string wordEnc = "xultpaajcxitltlxaarpjhtiwtgxktghidhipxciwtvgtpilpitghlxiwiwtxgqadds";

    //wordReplacer(wordEnc);
    charCounter(wordEnc);

}
