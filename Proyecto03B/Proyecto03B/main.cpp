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

#include "Encriptador.h"

/*
* Convierte una cadena de texto a minusculas
* Observación: Utiliza la función transform para convertir todos los caracteres de una cadena a minúsculas.
* @param:
*	- string& texto: Cadena de texto a convertir.
* @return:
*	+ string: Cadena de texto convertida a minúsculas.
*/
string convertirMinusculas(string& texto)
{
    transform(texto.begin(), texto.end(), texto.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
    return texto;
}

int main() 
{   
	// Version actual del programa
    Encriptador enc;
    string opcion;

	// Menú principal
	// Bucle infinito hasta que el usuario decida salir
	// Entrada y validación de la opción del usuario
    while (true)
    {
        cout << "Seleccione una opción: (e) Encriptar, (d) Desencriptar, (s) Salir: ";
        cin >> opcion;

        if (convertirMinusculas(opcion) != "e" && convertirMinusculas(opcion) != "d" && convertirMinusculas(opcion) != "s")
        {
            cout << "Opción no válida. Intente de nuevo." << endl;
			cout << "Solo se aceptan las opciones 'e', 'd' o 's'." << endl;
            continue;
        }
        else if (convertirMinusculas(opcion) == "e")
            cout << "\nHa seleccionado la opción de Encriptar un archivo." << endl;
        else if (convertirMinusculas(opcion) == "d")
            cout << "\nHa seleccionado la opción de Desencriptar un archivo." << endl;
        else if (convertirMinusculas(opcion) == "s")
        {
            cout << "Saliendo del Menu." << endl;
            break;
        }
        else
        {
			cout << "Error de Opcion." << endl;
			cout << "Solo se aceptan las opciones 'e', 'd' o 's'." << endl;
			continue;
        }

        string inputFile, outputFile;
        int tipo;
        cout << "Ingrese el archivo de entrada: ";
        cin >> inputFile;
        cout << "Ingrese el archivo de salida: ";
        cin >> outputFile;

        if (convertirMinusculas(opcion) == "e")
        {
            cout << "Seleccione el tipo de patrón de encriptación (1,2,3): ";
            cin >> tipo;
            enc.encriptar(inputFile, outputFile, tipo);
        }
        else if (convertirMinusculas(opcion) == "d")
            enc.desencriptar(inputFile, outputFile);
    }

    return 0;
}
