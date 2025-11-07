/*
* Proyecto 03A: Compresor y descompresor Huffman
* @Authors:
*   - Jeffry Araya Ch.
*   - Federick Fernandez C.
*   - Juan J. Rojas
*
* Created: 07/11/2025 10:50
* Modified: 
*/

#include <iostream>
#include "Huffman.h"

using namespace std;

int main()
{
    Huffman huffman;
    int opcion;
    string archivoEntrada, archivoSalida;

    cout << "Compresor Huffman\n";
    cout << "1. Comprimir\n2. Descomprimir\nOpción: ";
    cin >> opcion;

    cout << "Archivo de entrada: ";
    cin >> archivoEntrada;
    cout << "Archivo de salida: ";
    cin >> archivoSalida;

    if (opcion == 1) 
    {
        huffman.comprimir(archivoEntrada, archivoSalida);
        cout << "Archivo comprimido exitosamente.\n";
    }
    else if (opcion == 2) 
    {
        huffman.descomprimir(archivoEntrada, archivoSalida);
        cout << "Archivo descomprimido exitosamente.\n";
    }
    else
        cout << "Opción inválida.\n";

    return 0;
}