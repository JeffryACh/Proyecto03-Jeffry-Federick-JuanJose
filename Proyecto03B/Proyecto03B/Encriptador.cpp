#include "Encriptador.h"

Encriptador::Encriptador()
{
    generarClave();
}

/*
* Genera una clave de encriptación aleatoria
* Observación: La clave es una permutación de los 256 valores posibles de un byte
* @param:
*   - Ninguno
* @returns:
*   + Ninguno
*/
void Encriptador::generarClave() 
{
    clave.resize(256);
    for (int i = 0; i < 256; i++) 
        clave[i] = static_cast<unsigned char>(i);
    random_shuffle(clave.begin(), clave.end());
    construirClaveInversa();
}

/*
* Construye la clave inversa para desencriptación
* Observación: La clave inversa mapea cada valor cifrado de vuelta a su valor original
* @param:
*   - Ninguno
* @returns:
*   + Ninguno
*/
void Encriptador::construirClaveInversa() 
{
    claveInversa.resize(256);
    for (int i = 0; i < 256; i++) 
    {
        unsigned char original = static_cast<unsigned char>(i);
        unsigned char cifrado = clave[i];
        claveInversa[cifrado] = original;
    }
}

/*
* Encripta un archivo usando la clave generada
* Observación: La clave se guarda en el encabezado del archivo encriptado
* @param:
*   - string &pInputFile: Ruta del archivo a encriptar
*   - pOutputFile: Ruta donde se guardará el archivo encriptado
* @returns:
*   + Ninguno
*/
void Encriptador::encriptar(const string &pInputFile, const string &pOutputFile) 
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

    // Guardar la clave en el encabezado
    out.write(reinterpret_cast<const char*>(clave.data()), clave.size());

    char ch;
    while (in.get(ch)) 
    {
        unsigned char nuevo = clave[static_cast<unsigned char>(ch)];
        out.put(static_cast<char>(nuevo));
    }

    in.close();
    out.close();
    cout << "Archivo encriptado correctamente: " << pOutputFile << endl;
}

/*
* Desencripta un archivo usando la clave incluida en su encabezado
* @param:
*   - pInputFile: Ruta del archivo encriptado
*   - pOutputFile: Ruta donde se guardará el archivo desencriptado
* @returns:
*   + Ninguno
*/
void Encriptador::desencriptar(const string & pInputFile, const string & pOutputFile) 
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

    // Leer la clave del encabezado
    vector<unsigned char> claveLeida(256);
    in.read(reinterpret_cast<char*>(claveLeida.data()), claveLeida.size());

    // Construir clave inversa a partir de la clave leída
    vector<unsigned char> claveInv(256);
    for (int i = 0; i < 256; i++) {
        unsigned char cifrado = claveLeida[i];
        claveInv[cifrado] = static_cast<unsigned char>(i);
    }

    char ch;
    while (in.get(ch)) 
    {
        unsigned char original = claveInv[static_cast<unsigned char>(ch)];
        out.put(static_cast<char>(original));
    }

    in.close();
    out.close();
    cout << "Archivo desencriptado correctamente: " << pOutputFile << endl;
}
