#include "BitUtils.h"

/*
* Escribe una cadena de bits en un archivo binario.
* Observación: La cadena de bits debe tener una longitud múltiplo de 8.
* @param:
*   - string& pNombreArchivo: Nombre del archivo donde se escribirán los bits.
*   - string& pCadenaBits: Cadena de bits a escribir en el archivo.
* @return:
*   + void: No retorna valor.
*/
void UtilidadesBit::escribirBitsEnArchivo(const string& pNombreArchivo, const string& pCadenaBits) 
{
    ofstream archivo(pNombreArchivo, ios::binary);
    for (size_t i = 0; i < pCadenaBits.size(); i += 8) 
    {
        string byteCadena = pCadenaBits.substr(i, 8);
        while (byteCadena.size() < 8) byteCadena += '0';
        unsigned char byte = static_cast<unsigned char>(bitset<8>(byteCadena).to_ulong());
        archivo.put(byte);
    }
    archivo.close();
}

/*
* Lee una cadena de bits desde un archivo binario.
* Observación: El archivo debe contener datos en formato binario.
* @param:
*   - string& pNombreArchivo: Nombre del archivo desde donde se leerán los bits.
* @return:
*   + string: Cadena de bits leída del archivo.
*/
string UtilidadesBit::leerBitsDeArchivo(const string& pNombreArchivo) 
{
    ifstream archivo(pNombreArchivo, ios::binary);
    string cadenaBits;
    unsigned char byte;
    while (archivo.read(reinterpret_cast<char*>(&byte), 1))
        cadenaBits += bitset<8>(byte).to_string();
    archivo.close();
    return cadenaBits;
}