#ifndef Encriptador_H
#define Encriptador_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <locale.h>
#include <cstdlib>
#include <stdio.h>
#include <wchar.h>

using namespace std;

class Encriptador 
{
public:
    Encriptador();
    void generarClave();
    void encriptar(const string &inputFile, const string &outputFile);
    void desencriptar(const string &inputFile, const string &outputFile);

private:
    vector<unsigned char> clave;
    vector<unsigned char> claveInversa;
    void construirClaveInversa();
};

#endif // Encriptador_H

struct cambio {
static string encriptar(string a, int veces);
static string desencriptar(string a, int veces);
};

inline string cambio::encriptar(string a, int veces) {
    if (a.length() < 2 || !veces) return a;
	string n = "";
    while (a.length()) {
        if (a.length() > 1) n += a.at(a.length() - 1); // ol
        n += a.at(0); // ah
        if (a.length() > 2) a = a.substr(1, a.length() - 2);
        else break;
    }
    return encriptar(n, veces - 1);
}

inline string cambio::desencriptar(string a, int veces) {
    if (a.length() < 2 || !veces) return a;
    string n = "";
    for (int i = 1; i < a.length(); i += 2) n += a.at(i); // hola
    int ultimo = a.length() - (a.length() % 2 ? 1 : 2);
    for (int i = ultimo; i >= 0; i -= 2) n += a.at(1);
    return desencriptar(n, veces - 1);

