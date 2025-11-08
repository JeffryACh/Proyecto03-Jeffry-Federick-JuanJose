/*
* Proyecto 03A: Compresor y descompresor Huffman
* @Authors:
*   - Jeffry Araya Ch.
*   - Federick Fernandez C.
*   - Juan J. Rojas
*
* Created: 07/11/2025 10:50
* Modified: 08/11/2025 14:40
*/

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "Huffman.h"

using namespace std;

// Constantes para los tipos de archivo usando operaciones bitwise
const unsigned char TIPO_TXT = 0x01;   // 00000001
const unsigned char TIPO_BMP = 0x02;   // 00000010
const unsigned char TIPO_ZIP = 0x04;   // 00000100
const unsigned char TIPO_MP3 = 0x08;   // 00001000
const unsigned char TIPO_MP4 = 0x10;   // 00010000
const unsigned char TIPO_JPG = 0x20;   // 00100000
const unsigned char TIPO_EXE = 0x40;   // 01000000

/*
* Limpia el buffer de entrada estándar.
* Observación: Útil para manejar entradas inválidas.
* @param:
*   - Ninguno.
* @return:
*   + void: No retorna valor.
*/
void limpiarBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
* Verifica si un archivo existe y es accesible.
* Observación: Utiliza operaciones de flujo de archivos.
* @param:
*   - const string& pNombreArchivo: Nombre del archivo a verificar.
* @return:
*   + bool: true si el archivo existe y es accesible, false en caso contrario.
*/
bool archivoExiste(const string& pNombreArchivo) 
{
    ifstream archivo(pNombreArchivo.c_str());
    return archivo.good();
}

/*
* Obtiene la extensión de un archivo.
* Observación: Retorna una cadena vacía si no hay extensión.
* @param:
*   - const string& pNombreArchivo: Nombre del archivo.
* @return:
*   + string: Extensión del archivo incluyendo el punto (.), o cadena vacía si no hay extensión.
*/
string obtenerExtension(const string& pNombreArchivo)
{
    size_t pos = pNombreArchivo.find_last_of(".");
    if (pos != string::npos) 
        return pNombreArchivo.substr(pos);
    return "";
}

/*
* Obtiene el nombre del archivo sin su extensión.
* Observación: Retorna el nombre completo si no hay extensión.
* @param:
*   - const string& pNombreArchivo: Nombre del archivo.
* @return:
*   + string: Nombre del archivo sin la extensión.
*/
string obtenerNombreSinExtension(const string& pNombreArchivo) 
{
    size_t pos = pNombreArchivo.find_last_of(".");
    if (pos != string::npos) 
        return pNombreArchivo.substr(0, pos);
    return pNombreArchivo;
}

/*
* Obtiene una opción válida del usuario dentro de un rango específico.
* Observación: Maneja entradas inválidas y fuera de rango.
* @param:
*   - int pMin: Valor mínimo válido (inclusive).
*   - int pMax: Valor máximo válido (inclusive).
*   - const string& pMensaje: Mensaje a mostrar al usuario.
* @return:
*   + int: Opción válida ingresada por el usuario.
*/
int obtenerOpcionValida(int pMin, int pMax, const string& pMensaje)
{
    int opcion;
    bool entradaValida = false;
    
    do {
        cout << pMensaje;
        if (cin >> opcion) 
        {
            // Verificar si el número está en el rango válido
            if (opcion >= pMin && opcion <= pMax) 
                entradaValida = true;
            else 
            {
                cout << "Error: La opción " << opcion << " no existe en el menú.\n";
                cout << "Por favor seleccione una opción entre " << pMin << " y " << pMax << ".\n";
            }
        } 
        else 
        {
            cout << "Error: Entrada inválida. Por favor ingrese un número.\n";
            limpiarBuffer();
        }
    } while (!entradaValida);
    
    return opcion;
}

/*
* Muestra el menú de formatos de compresión y obtiene la selección del usuario.
* Observación: Utiliza la función de validación de opciones.
* @param:
*   - Ninguno.
* @return:
*   + string: Extensión del formato de compresión seleccionado.
*/
string mostrarMenuCompresion() 
{
    cout << "\nSeleccione el formato de compresión:\n";
    cout << "1. ZIP\n";
    cout << "2. MP3\n";
    cout << "3. MP4\n";
    cout << "4. JPG\n";
    cout << "5. EXE\n";
    
    int opcion = obtenerOpcionValida(1, 5, "Opción: ");
    
    switch (opcion) 
    {
        case 1: return ".zip";
        case 2: return ".mp3";
        case 3: return ".mp4";
        case 4: return ".jpg";
        case 5: return ".exe";
        default: return "";
    }
}

int main()
{
    Huffman huffman;
    string archivoEntrada, archivoSalida;

    cout << "Compresor Huffman\n";
    
    // Menú principal con validación
    int opcionPrincipal = obtenerOpcionValida(1, 2, 
        "1. Comprimir\n"
        "2. Descomprimir\n"
        "Opción: ");

    if (opcionPrincipal == 1)
    {
        // Menú de tipo de archivo con validación
        cout << "\nSeleccione el tipo de archivo a comprimir:\n";
        cout << "1. Archivo de texto (.txt)\n";
        cout << "2. Imagen BMP (.bmp)\n";
        
        int tipoArchivo = obtenerOpcionValida(1, 2, "Opción: ");

        // Determinar archivo de entrada según tipo
        archivoEntrada = (tipoArchivo == 1) ? "entrada.txt" : "entrada.bmp";
        
        // Verificar existencia del archivo usando AND
        if (!archivoExiste(archivoEntrada)) 
        {
            cout << "Error: El archivo " << archivoEntrada << " no existe o no es accesible.\n";
            return 1;
        }

        // Obtener formato de compresión con validación integrada
        string extension = mostrarMenuCompresion();
        
        // Usar XOR para generar marca de compresión
        unsigned char tipoMarca = (tipoArchivo == 1) ? TIPO_TXT : TIPO_BMP;
        unsigned char marcaCompresion = tipoMarca ^ 0xFF;
        archivoSalida = obtenerNombreSinExtension(archivoEntrada) + extension;
      
        huffman.comprimir(archivoEntrada, archivoSalida);
        cout << "Archivo comprimido exitosamente como: " << archivoSalida << endl;
    }
    else // opcionPrincipal == 2
    { 
        // Menú de tipo de archivo comprimido con validación
        cout << "\nSeleccione el tipo de archivo comprimido:\n";
        cout << "1. ZIP (.zip)\n";
        cout << "2. MP3 (.mp3)\n";
        cout << "3. MP4 (.mp4)\n";
        cout << "4. JPG (.jpg)\n";
        cout << "5. EXE (.exe)\n";
 
        int formatoComprimido = obtenerOpcionValida(1, 5, "Opción: ");
        string extension = "." + string(formatoComprimido == 1 ? "zip" : 
            formatoComprimido == 2 ? "mp3" :
            formatoComprimido == 3 ? "mp4" :
            formatoComprimido == 4 ? "jpg" : "exe");
        
        archivoEntrada = "entrada" + extension;
  
        // Verificar archivo comprimido usando OR
        if (!archivoExiste(archivoEntrada)) 
        {
            cout << "Error: El archivo comprimido " << archivoEntrada << " no existe o no es accesible.\n";
            return 1;
        }

        // Submenú para seleccionar el tipo de archivo de salida
        cout << "\nSeleccione el tipo de archivo a descomprimir:\n";
        cout << "1. Archivo de texto (.txt)\n";
        cout << "2. Imagen BMP (.bmp)\n";
        
        int tipoArchivoSalida = obtenerOpcionValida(1, 2, "Opción: ");
      
        // Usar operaciones bitwise para determinar la extensión
        unsigned char tipoSalida = (tipoArchivoSalida == 1) ? TIPO_TXT : TIPO_BMP;
        // Usar NOT para invertir los bits del tipo de archivo comprimido
        unsigned char formatoOriginal = ~(1 << (formatoComprimido - 1)) & tipoSalida;
        string extensionOriginal = (tipoArchivoSalida == 1) ? ".txt" : ".bmp";
 
        archivoSalida = "Descomprimido" + obtenerNombreSinExtension(archivoEntrada) + extensionOriginal;
      
        huffman.descomprimir(archivoEntrada, archivoSalida);
        cout << "Archivo descomprimido exitosamente como: " << archivoSalida << endl;
    }

    return 0;
}