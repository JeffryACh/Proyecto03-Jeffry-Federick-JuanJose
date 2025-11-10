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
    void encriptar(const string &inputFile, const string &outputFile, int tipo);
    void desencriptar(const string &inputFile, const string &outputFile);

private:
    vector<unsigned char> clave;
    vector<unsigned char> claveInversa;
    void construirClaveInversa();
    unsigned char aplicarPatron(unsigned char byte, int tipo);
    unsigned char revertirPatron(unsigned char byte, int tipo);
};

#endif // Encriptador_H