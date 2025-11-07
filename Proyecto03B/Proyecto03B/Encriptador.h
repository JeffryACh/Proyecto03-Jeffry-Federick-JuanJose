#ifndef Encriptador_H
#define Encriptador_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

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
