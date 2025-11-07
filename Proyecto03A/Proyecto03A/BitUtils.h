#pragma once
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