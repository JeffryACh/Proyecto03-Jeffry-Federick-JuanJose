#include "Encriptador.h"

Encriptador::Encriptador()
{
    generarClave();
}

/*
* Genera una clave de encriptación aleatoria
* Observación: La clave es una permutación de los 256 valores posibles de un byte
* @param:
* - Ninguno
* @returns:
* + Ninguno
*/
void Encriptador::generarClave() 
{
    clave.resize(256);
    for (int i =0; i <256; i++) 
        clave[i] = static_cast<unsigned char>(i);
    random_shuffle(clave.begin(), clave.end());
    construirClaveInversa();
}

/*
* Construye la clave inversa para desencriptación
* Observación: La clave inversa mapea cada valor cifrado de vuelta a su valor original
* @param:
* - Ninguno
* @returns:
* + Ninguno
*/
void Encriptador::construirClaveInversa() 
{
    claveInversa.resize(256);
    for (int i =0; i <256; i++) 
    {
        unsigned char original = static_cast<unsigned char>(i);
        unsigned char cifrado = clave[i];
        claveInversa[cifrado] = original;
    }
}

/*
* Aplica un patrón de encriptación al byte
* @param:
* - unsigned char byte: Byte a encriptar
* - int tipo: Tipo de patrón de encriptación
* @returns:
* + unsigned char: Byte encriptado
*/
unsigned char Encriptador::aplicarPatron(unsigned char byte, int tipo) 
{
    switch (tipo) 
    {
        case1: // Inversión de bits
            return ~byte;
        case2: // Inversión de bits por posición
            return ((byte &0xF0) >>4) | ((byte &0x0F) <<4);
        case3: // Máscara10101010
            return byte ^0xAA;
        default:
            return byte;
    }
}

/*
* Revertir un patrón de encriptación al byte
* @param:
* - unsigned char byte: Byte a desencriptar
* - int tipo: Tipo de patrón de desencriptación
* @returns:
* + unsigned char: Byte desencriptado
*/
unsigned char Encriptador::revertirPatron(unsigned char byte, int tipo) 
{
 return aplicarPatron(byte, tipo); // Los patrones son reversibles
}

/*
* Encripta un archivo usando un patrón de encriptación
* Observación: El patrón se guarda en el encabezado del archivo encriptado
* @param:
* - string &pInputFile: Ruta del archivo a encriptar
* - string &pOutputFile: Ruta donde se guardará el archivo encriptado
* - int tipo: Tipo de patrón de encriptación
* @returns:
* + Ninguno
*/
void Encriptador::encriptar(const string &pInputFile, const string &pOutputFile, int tipo) 
{
    ifstream in(pInputFile, ios::binary);
    if (!in) 
    {
        cerr << "Error al abrir el archivo original para encriptar." << endl;
        return;
    }

    ofstream out(pOutputFile, ios::binary);
    if (!out) 
    {
        cerr << "Error al crear el archivo encriptado." << endl;
        return;
    }

    // Guardar el tipo de patrón en el encabezado
    out.put(static_cast<char>(tipo));

    char ch;
    while (in.get(ch)) 
    {
        unsigned char nuevo = aplicarPatron(static_cast<unsigned char>(ch), tipo);
        out.put(static_cast<char>(nuevo));
    }

    in.close();
    out.close();
    cout << "Archivo encriptado correctamente: " << pOutputFile << endl;
}

/*
* Desencripta un archivo usando un patrón de desencriptación
* @param:
* - string pInputFile: Ruta del archivo encriptado
* - string pOutputFile: Ruta donde se guardará el archivo desencriptado
* @returns:
* + Ninguno
*/
void Encriptador::desencriptar(const string &pInputFile, const string &pOutputFile) 
{
    ifstream in(pInputFile, ios::binary);
    if (!in) 
    {
        cerr << "Error al abrir el archivo encriptado para desencriptar." << endl;
        return;
    }

    ofstream out(pOutputFile, ios::binary);
    if (!out) 
    {
        cerr << "Error al crear el archivo restaurado." << endl;
        return;
    }

    // Leer el tipo de patrón del encabezado
    int tipo = in.get();

    char ch;
    while (in.get(ch)) 
    {
        unsigned char original = revertirPatron(static_cast<unsigned char>(ch), tipo);
        out.put(static_cast<char>(original));
    }

    in.close();
    out.close();
    cout << "Archivo desencriptado correctamente: " << pOutputFile << endl;
}



