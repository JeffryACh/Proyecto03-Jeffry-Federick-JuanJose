#include "Huffman.h"

Nodo::Nodo(char pDato, int pFrecuencia) : dato(pDato), frecuencia(pFrecuencia), izquierdo(nullptr), derecho(nullptr) {}

struct Comparar 
{
    bool operator()(Nodo* pA, Nodo* pB) 
    {
        return pA->frecuencia > pB->frecuencia;
    }
};

/*
* Comprime un archivo utilizando el algoritmo de Huffman.
* Observación: El archivo de entrada debe existir y ser accesible.
* @param:
*   - string& pArchivoEntrada: Nombre del archivo a comprimir.
*   - string& pArchivoSalida: Nombre del archivo donde se guardará el archivo comprimido.
* @return:
*   + void: No retorna valor.
*/
void Huffman::comprimir(const string& pArchivoEntrada, const string& pArchivoSalida) 
{
    unordered_map<char, int> frecuencias;
    construirTablaFrecuencias(pArchivoEntrada, frecuencias);

    Nodo* raiz = construirArbol(frecuencias);
    unordered_map<char, string> codigos;
    generarCodigos(raiz, "", codigos);

    escribirComprimido(pArchivoEntrada, pArchivoSalida, codigos);
}

/*
* Descomprime un archivo utilizando el algoritmo de Huffman.
* Observación: El archivo de entrada debe existir y ser accesible.
* @param:
*   - string& pArchivoEntrada: Nombre del archivo a descomprimir.
*   - string& pArchivoSalida: Nombre del archivo donde se guardará el archivo descomprimido.
* @return:
*   + void: No retorna valor.
*/
void Huffman::descomprimir(const string& pArchivoEntrada, const string& pArchivoSalida) 
{
    leerComprimido(pArchivoEntrada, pArchivoSalida);
}

/*
* Construye una tabla de frecuencias de caracteres a partir de un archivo.
* Observación: El archivo de entrada debe existir y ser accesible.
* @param:
*   - string& pArchivoEntrada: Nombre del archivo desde donde se leerán los caracteres.
*   - unordered_map<char, int>& pFrecuencias: Mapa donde se almacenarán las frecuencias de los caracteres.
* @return:
*   + void: No retorna valor.
*/
void Huffman::construirTablaFrecuencias(const string& pArchivoEntrada, unordered_map<char, int>& pFrecuencias) 
{
    ifstream archivo(pArchivoEntrada, ios::binary);
    char caracter;
    while (archivo.get(caracter)) pFrecuencias[caracter]++;
    archivo.close();
}

/*
* Construye el árbol de Huffman a partir de una tabla de frecuencias.
* Observación: La tabla de frecuencias no debe estar vacía.
* @param:
*   - unordered_map<char, int>& pFrecuencias: Mapa con las frecuencias de los caracteres.
* @return:
*   + Nodo*: Puntero a la raíz del árbol de Huffman construido.
*/
Nodo* Huffman::construirArbol(const unordered_map<char, int>& pFrecuencias) 
{
    priority_queue<Nodo*, vector<Nodo*>, Comparar> colaPrioridad;
    for (auto& par : pFrecuencias) 
        colaPrioridad.push(new Nodo(par.first, par.second));

    while (colaPrioridad.size() > 1) 
    {
        Nodo* izq = colaPrioridad.top(); colaPrioridad.pop();
        Nodo* der = colaPrioridad.top(); colaPrioridad.pop();
        Nodo* fusion = new Nodo('\0', izq->frecuencia + der->frecuencia);
        fusion->izquierdo = izq;
        fusion->derecho = der;
        colaPrioridad.push(fusion);
    }
    return colaPrioridad.top();
}

/*
* Genera los códigos binarios para cada carácter a partir del árbol de Huffman.
* Observación: El árbol de Huffman no debe estar vacío.
* @param:
*   - Nodo* pRaiz: Puntero a la raíz del árbol de Huffman.
*   - string pCodigo: Código binario acumulado hasta el nodo actual.
*   - unordered_map<char, string>& pCodigos: Mapa donde se almacenarán los códigos binarios de los caracteres.
* @return:
*   + void: No retorna valor.
*/
void Huffman::generarCodigos(Nodo* pRaiz, string pCodigo, unordered_map<char, string>& pCodigos)
{
    if (!pRaiz) return;
    if (pRaiz->dato != '\0') pCodigos[pRaiz->dato] = pCodigo;
    generarCodigos(pRaiz->izquierdo, pCodigo + "0", pCodigos);
    generarCodigos(pRaiz->derecho, pCodigo + "1", pCodigos);
}

/*
* Escribe el archivo comprimido utilizando los códigos binarios generados.
* Observación: El archivo de entrada debe existir y ser accesible.
* @param:
*   - string& pArchivoEntrada: Nombre del archivo a comprimir.
*   - string& pArchivoSalida: Nombre del archivo donde se guardará el archivo comprimido.
*   - unordered_map<char, string>& pCodigos: Mapa con los códigos binarios de los caracteres.
* @return:
*   + void: No retorna valor.
*/
void Huffman::escribirComprimido(const string& pArchivoEntrada, const string& pArchivoSalida, const unordered_map<char, string>& pCodigos)
{
    ifstream archivo(pArchivoEntrada, ios::binary);
    string cadenaBits;
    char caracter;
    while (archivo.get(caracter)) cadenaBits += pCodigos.at(caracter);
    archivo.close();

    UtilidadesBit::escribirBitsEnArchivo(pArchivoSalida, cadenaBits);
}

/*
* Lee el archivo comprimido y lo descomprime utilizando el árbol de Huffman.
* Observación: El archivo de entrada debe existir y ser accesible.
* @param:
*   - string& pArchivoEntrada: Nombre del archivo comprimido a leer.
*   - string& pArchivoSalida: Nombre del archivo donde se guardará el archivo descomprimido.
* @return:
*   + void: No retorna valor.
*/
void Huffman::leerComprimido(const string& pArchivoEntrada, const string& pArchivoSalida) 
{
    string bits = UtilidadesBit::leerBitsDeArchivo(pArchivoEntrada);
    ofstream archivo(pArchivoSalida, ios::binary);
    archivo << bits; // Aquí se debe decodificar usando el árbol (pendiente)
    archivo.close();
}