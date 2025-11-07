/*
* Proyecto 03B: Encriptador de Archivos
* @Authors:
*   - Jeffry Araya Ch.
*   - Federick Fernandez C.
*   - Juan J. Rojas
*
* Created: 07/11/2025 10:50
* Modified: 07/11/2025 14:10
*/

#include <iostream>
#include "Encriptador.h"

int main() 
{
    Encriptador enc;
    string opcion;
    cout << "Seleccione una opción: (e) Encriptar, (d) Desencriptar: ";
    cin >> opcion;

    string inputFile, outputFile;
    cout << "Ingrese el archivo de entrada: ";
    cin >> inputFile;
    cout << "Ingrese el archivo de salida: ";
    cin >> outputFile;

    if (opcion == "e") 
        enc.encriptar(inputFile, outputFile);
     else if (opcion == "d") 
        enc.desencriptar(inputFile, outputFile);
     else 
        cout << "Opción no válida." << endl;

    return 0;
}
