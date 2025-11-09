/*
* Proyecto 03B: Encriptador de Archivos
* @Authors:
*   - Jeffry Araya Ch.
*   - Federick Fernandez C.
*   - Juan J. Rojas
*
* Created: 07/11/2025 10:50
* Modified: 08/11/2025 21:30
*/

#include <iostream>
#include "Encriptador.h"

int main() 
{   
	// Version actual del programa
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
    setlocale(LC_ALL, "");
    system("cls");

    string msg;
    int clave;
    while (1) {
        cout << "\n" << "Programa de cifrado mediante mezclado de caracteres" << endl;
        cout << "\n" << "Elija una opcion:" << endl;
        cout << " Encriptar: #1" << "\n" << " Desencriptar: #2" << endl;
        char opt;
        do opt = _getch();
        while (opt != '1' && opt != '2');
        system("cls");
        cout << " Digite el numero de clave" << endl;
        cin >> clave;
        cout << "Escribe el dato" << endl;
        cin >> ws;
        getline(cin, msg);
        if (opt == '1')
        {
            string nuevo = cambio::encriptar2(msg, clave);
            cout << "dato encriptado " << nuevo << " " << endl;
        }
        else 
        {
            string nuevo = cambio::desencriptar2(msg, clave);
            cout << "dato desencriptado " << nuevo << " " << endl;
        }
        _getch();

        system("cls");
    }
    return 0;
}
