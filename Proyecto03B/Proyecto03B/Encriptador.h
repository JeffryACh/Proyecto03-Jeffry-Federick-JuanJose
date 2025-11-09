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



struct cambio 
{
static string encriptar2(string a, int veces);
static string desencriptar2(string a, int veces);
};

/*
* Funciones de encriptación mediante mezcla de caracteres
* Observación: Estas funciones realizan un proceso de mezcla de caracteres
* @param:
*   - string a: Cadena a encriptar o desencriptar
*   - int veces: Número de veces que se aplicará el proceso
* @returns:
*   + string: Cadena encriptada o desencriptada
*/
inline string cambio::encriptar2(string a, int veces) 
{
    if (a.length() < 2 || !veces) return a;
	string n = "";
    while (a.length()) 
    {
        if (a.length() > 1) n += a.at(a.length() - 1); 
        n += a.at(0); // ah
        if (a.length() > 2) a = a.substr(1, a.length() - 2);
        else break;
    }
    return encriptar2(n, veces - 1);
}

/*
* Función de desencriptación mediante mezcla de caracteres
* Observación: Esta función revierte el proceso de mezcla de caracteres
* @param:
*   - string a: Cadena a desencriptar
*   - int veces: Número de veces que se aplicará el proceso inverso
* @returns:
*   + string: Cadena desencriptada
*/
inline string cambio::desencriptar2(string a, int veces) 
{
    if (a.length() < 2 || !veces) return a;
    string n = "";
    for (int i = 1; i < a.length(); i += 2) n += a.at(i); 
    int ultimo = a.length() - (a.length() % 2 ? 1 : 2);
    for (int i = ultimo; i >= 0; i -= 2) n += a.at(1);
    return desencriptar2(n, veces - 1);
}

#endif // Encriptador_H