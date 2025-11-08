#ifndef Huffman_H
#define Huffman_H
#include <fstream>
#include <queue>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "BitUtils.h"

using namespace std;

struct Nodo 
{
    char dato;
    int frecuencia;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo(char pDato, int pFrecuencia);
};

class Huffman 
{
public:
    void comprimir(const string& pArchivoEntrada, const string& pArchivoSalida);
    void descomprimir(const string& pArchivoEntrada, const string& pArchivoSalida);

private:
    void construirTablaFrecuencias(const string& pArchivoEntrada, unordered_map<char, int>& pFrecuencias);
    Nodo* construirArbol(const unordered_map<char, int>& pFrecuencias);
    void generarCodigos(Nodo* pRaiz, string pCodigo, unordered_map<char, string>& pCodigos);
    void escribirComprimido(const string& pArchivoEntrada, const string& pArchivoSalida, const unordered_map<char, string>& pCodigos, const unordered_map<char, int>& pFrecuencias);
};

#endif // Huffman_H