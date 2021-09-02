#include <iostream>
#include <string>

using namespace std;

class alfabeto
{
public:
    int sizeAlpha;
    char* alpha;
    int sizeVocales;
    char* vocales;

    alfabeto(string cadena = "abcdefghijklmnopqrstuvwxyz", string uvocales = "aeiou")
    {
        sizeAlpha = cadena.length();
        alpha = new char[sizeAlpha];
        sizeVocales = uvocales.length();
        vocales = new char[sizeVocales];

        for (int i = 0; i < sizeAlpha; i++)
        {
            alpha[i] = cadena[i];
        }

        for (int i = 0; i < sizeVocales; i++)
        {
            vocales[i] = uvocales[i];
        }


    }

    bool inVocales(char a)
    {
        a = tolower(a);
        for (int i = 0; i < sizeVocales; i++)
        {
            if (a == vocales[i] && a != ' ') return true;
        }
        return false;
    }

};

bool inString(char a, string cadena)
{
    a = tolower(a);
    for (int i = 0; i < (int)cadena.length(); i++)
    {
        if (a == cadena[i]) return true;
    }
    return false;
}

int modulo(int a, int b)
{
    int q = a / b;
    int res = a - (q * b);

    if (res < 0)
    {
        q--;
        res = a - (q * b);

    }

    return res;
}

string encrypt(string message, int key, alfabeto cesarAlph)
{
    int length = message.length();
    string encrypted(length, ' ');

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < cesarAlph.sizeAlpha; j++)
        {
            if (message[i] == cesarAlph.alpha[j])
            {
                encrypted[i] = cesarAlph.alpha[modulo(j + key, cesarAlph.sizeAlpha)];//MODULO
            }
            else if (tolower(message[i]) == cesarAlph.alpha[j])
            {
                encrypted[i] = toupper(cesarAlph.alpha[modulo(j + key, cesarAlph.sizeAlpha)]);
            }
        }
    }

    return encrypted;
}

string decrypt(string message, int key, alfabeto cesarAlph)
{
    int length = message.length();
    string encrypted(length, ' ');

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < cesarAlph.sizeAlpha; j++)
        {
            if (message[i] == cesarAlph.alpha[j])
            {
                encrypted[i] = cesarAlph.alpha[modulo(j - key, cesarAlph.sizeAlpha)];//MODULO
            }
            else if (tolower(message[i]) == cesarAlph.alpha[j])
            {
                encrypted[i] = toupper(cesarAlph.alpha[modulo(j - key, cesarAlph.sizeAlpha)]);
            }

        }
    }

    return encrypted;
}

string forceDecrypt(string mensaje, alfabeto cesarAlph = alfabeto("abcdefghijklmnopqrstuvwxyz"))
{
    char userSel;
    string temp;
    for (int i = 0; i < cesarAlph.sizeAlpha; i++)
    {
        temp = decrypt(mensaje, i, cesarAlph);
        cout << "Es este el mensaje adecuado?: " << temp << endl;
        cout << "Ingrese (y/N) : ";
        cin >> userSel;
        if (userSel == 'y' || userSel == 'Y') return temp;
    }
    return temp;
}

string smartDecrypt(string mensaje, alfabeto cesarAlph = alfabeto("abcdefghijklmnopqrstuvwxyz"))
{
    int point = 0;
    int key = 0;
    string temp;
    int menLen = mensaje.length();
    int res = modulo(menLen, 3);

    for (int i = 0; i < cesarAlph.sizeAlpha; i++)
    {
        int newPoint = 0;
        temp = decrypt(mensaje, i, cesarAlph);
        
        for (int j = 0; j < (int)temp.length() - 1; j++)
        {
            // [p, b, d, t, k, g] o el sonido [f] + los sonidos líquidos [l] o [ɾ].

            if (j < (int)temp.length() - 2 && !cesarAlph.inVocales(temp[j]) && cesarAlph.inVocales(temp[j + 1]) && !cesarAlph.inVocales(temp[j + 2]))
            {
                newPoint += 10;
            }
            else if (j < (int)temp.length() - 2 && !cesarAlph.inVocales(temp[j]) && !cesarAlph.inVocales(temp[j + 1]) && !cesarAlph.inVocales(temp[j + 2]))
            {
                newPoint -= 30;
                break;
            }
            else if (cesarAlph.inVocales(temp[j]) && !cesarAlph.inVocales(temp[j + 1]))
            {
                newPoint += 6;
            }
            else if (cesarAlph.inVocales(temp[j]) && cesarAlph.inVocales(temp[j + 1]))
            {
                newPoint += 4;
            }
            else if (inString(temp[j], "pbdtkgc"))
            {
                if (inString(temp[j + 1], "lr")) newPoint += 3;
                else if (temp[j] == 'c' && temp[j + 1] == 'h') newPoint += 5;
                else if (!cesarAlph.inVocales(temp[j + 1])) newPoint -= 5;
            }

            
            if (temp[j] == 'e' || temp[j] == 'a')
            {
                newPoint += 2;
            }
            
            if (temp[j] == 'o' || temp[j] == 's')
            {
                newPoint += 1;
            }
        }

        if (newPoint > 0)
        {
            //cout << "Mensaje: " << decrypt(mensaje, i, cesarAlph);
            //cout << "\tPuntos:\t" << newPoint << endl;
        }
        if (newPoint > point)
        {
            point = newPoint;
            key = i;
        }
    }
    //cout << "El supuesto mensaje decifrado es: " << decrypt(mensaje, key, cesarAlph) << endl;
    cout << "La suspuesta llave es: " << key << endl;
    return decrypt(mensaje, key, cesarAlph);

}

int main()
{
    cout << smartDecrypt("ymnxerjxxfljenxestyerjfsyeytegjeijhtijiegzyenkectzeiteqjyerjeyjqqectzercekwnjsieymfyectzefwjevznyjefrfdnsl ", alfabeto("abcdefghijklmnopqrstuvwxyz "));
    
    int clave;
    string mensaje;

    cout << "Ingrese una clave: ";
    cin >> clave;
    cout << "Ingrese un mensaje: ";
    cin.ignore();
    getline(cin, mensaje);
    alfabeto miAlfabeto;

    string encriptado = encrypt(mensaje, clave, miAlfabeto);
    cout << "El mensaje encriptado es: " << encriptado << endl;
    // string desencriptada = smartDecrypt(mensaje, miAlfabeto);
    string desencriptada = smartDecrypt(encriptado, miAlfabeto);
    cout << "El algoritmo inteligente adivina que es: " << desencriptada << endl;
    desencriptada = decrypt(encriptado, clave, miAlfabeto);
    cout << "El mensaje desencriptado es: " << desencriptada << endl;
    

    return 0;
}
