#ifndef BitUtils_H
#define BitUtils_H
#include <string>
#include <vector>
#include <fstream>
#include <bitset>

using namespace std;

class UtilidadesBit 
{
public:
    static void escribirBitsEnArchivo(const string& pNombreArchivo, const string& pCadenaBits);
    static string leerBitsDeArchivo(const string& pNombreArchivo);
};

#endif // BitUtils_H