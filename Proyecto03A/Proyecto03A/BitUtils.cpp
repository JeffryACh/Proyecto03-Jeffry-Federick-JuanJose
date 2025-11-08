#include "BitUtils.h"

/*
* Escribe una cadena de bits en un archivo binario.
* Observación: Utiliza operaciones bit a bit para optimizar la escritura.
* @param:
*   - const string& pCadenaBits: Cadena de bits a escribir.
*   - ofstream& pArchivo: Archivo de salida en modo binario.
* @return:
*   + void: No retorna valor.
*/
void UtilidadesBit::escribirBitsEnArchivo(const string& pCadenaBits, ofstream& pArchivo)
{
    // Procesar la cadena de bits en grupos de 8
    for (size_t i = 0; i < pCadenaBits.size(); i += 8)
    {
        string byteCadena = pCadenaBits.substr(i, 8);
        while (byteCadena.size() < 8)
            byteCadena += '0';  // Padding con ceros

        // Usar operaciones bit a bit para construir el byte
        unsigned char byte = 0;
        for (int j = 0; j < 8; j++)
        {
            // Usar OR para establecer bits
            if (byteCadena[j] == '1')
                byte |= (1 << (7 - j));
        }
        pArchivo.put(static_cast<char>(byte));
    }
}

/*
* Lee una cadena de bits desde un archivo binario.
* Observación: Utiliza operaciones bit a bit para optimizar la lectura.
* @param:
*   - const string& pNombreArchivo: Nombre del archivo de entrada.
* @return:
*   + string: Cadena de bits leída del archivo.
*/
string UtilidadesBit::leerBitsDeArchivo(const string& pNombreArchivo)
{
    ifstream archivo(pNombreArchivo, ios::binary);
    string cadenaBits;
    unsigned char byte;

    while (archivo.read(reinterpret_cast<char*>(&byte), 1))
    {
        // Usar AND para extraer cada bit
        for (int i = 7; i >= 0; i--)
            cadenaBits += (byte & (1 << i)) ? '1' : '0';
    }

    archivo.close();
    return cadenaBits;
}