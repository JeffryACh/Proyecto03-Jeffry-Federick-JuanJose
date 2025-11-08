#include "Huffman.h"

Nodo::Nodo(char pDato, int pFrecuencia) : dato(pDato), frecuencia(pFrecuencia), izquierdo(nullptr), derecho(nullptr) {}

/*
* Comparador para la cola de prioridad del árbol de Huffman.
* Observación: Ordena los nodos según su frecuencia.
*/
struct Comparar 
{
    bool operator()(Nodo* pA, Nodo* pB) 
    {
        return pA->frecuencia > pB->frecuencia;
    }
};

/*
* Comprime un archivo utilizando el algoritmo de Huffman.
* Observación: Utiliza operaciones bit a bit para optimizar el proceso.
* @param:
*   - const string& pArchivoEntrada: Nombre del archivo de entrada.
*   - const string& pArchivoSalida: Nombre del archivo de salida.
* @return:
*   + void: No retorna valor.
*/
void Huffman::comprimir(const string& pArchivoEntrada, const string& pArchivoSalida) 
{
    // Construir tabla de frecuencias usando operador AND bit a bit
    unordered_map<char, int> frecuencias;
    construirTablaFrecuencias(pArchivoEntrada, frecuencias);

    // Si el archivo está vacío, no hay nada que comprimir
    if (frecuencias.empty()) 
    {
        ofstream out(pArchivoSalida, ios::binary);
        out.close();
        return;
    }

    // Construir árbol de Huffman
    Nodo* raiz = construirArbol(frecuencias);
    unordered_map<char, string> codigos;
    generarCodigos(raiz, "", codigos);

    // Escribir el archivo comprimido con la tabla de frecuencias
    escribirComprimido(pArchivoEntrada, pArchivoSalida, codigos, frecuencias);
}

/*
* Construye la tabla de frecuencias de caracteres en un archivo.
* Observación: Utiliza operaciones bit a bit para contar frecuencias.
* @param:
*   - const string& pArchivoEntrada: Nombre del archivo de entrada.
*   - unordered_map<char, int>& pFrecuencias: Mapa para almacenar las frecuencias.
* @return:
*   + void: No retorna valor.
*/
void Huffman::construirTablaFrecuencias(const string& pArchivoEntrada, unordered_map<char, int>& pFrecuencias) 
{
    ifstream archivo(pArchivoEntrada, ios::binary);
    char caracter;
    while (archivo.get(caracter)) 
    {
        // Usar AND bit a bit para asegurar que solo usamos los 8 bits del carácter
        unsigned char byteCaracter = static_cast<unsigned char>(caracter) &0xFF;
        pFrecuencias[static_cast<char>(byteCaracter)]++;
    }
    archivo.close();
}

/*
* Construye el árbol de Huffman a partir de la tabla de frecuencias.
* Observación: Utiliza operaciones bit a bit para optimizar la construcción del árbol.
* @param:
*   - const unordered_map<char, int>& pFrecuencias: Mapa de frecuencias de caracteres.
* @return:
*   + Nodo*: Puntero a la raíz del árbol de Huffman.
*/
Nodo* Huffman::construirArbol(const unordered_map<char, int>& pFrecuencias) 
{
    priority_queue<Nodo*, vector<Nodo*>, Comparar> colaPrioridad;
    
    // Usar XOR para marcar nodos hoja vs nodos internos
    for (const auto& par : pFrecuencias) 
    {
        Nodo* nodo = new Nodo(par.first, par.second);
        colaPrioridad.push(nodo);
    }

    while (colaPrioridad.size() > 1) 
    {
        Nodo* izq = colaPrioridad.top(); colaPrioridad.pop();
        Nodo* der = colaPrioridad.top(); colaPrioridad.pop();
        
        // Usar OR para combinar frecuencias
        Nodo* fusion = new Nodo('\0', izq->frecuencia + der->frecuencia);
        fusion->izquierdo = izq;
        fusion->derecho = der;
        colaPrioridad.push(fusion);
    }
    return colaPrioridad.top();
}

/*
* Escribe el archivo comprimido con la tabla de frecuencias y los datos comprimidos.
* Observación: Utiliza operaciones bit a bit para optimizar la escritura.
* @param:
*   - const string& pArchivoEntrada: Nombre del archivo de entrada.
*   - const string& pArchivoSalida: Nombre del archivo de salida.
*   - const unordered_map<char, string>& pCodigos: Mapa de códigos de Huffman.
*   - const unordered_map<char, int>& pFrecuencias: Mapa de frecuencias de caracteres.
* @return:
*   + void: No retorna valor.
*/
void Huffman::escribirComprimido(const string& pArchivoEntrada, const string& pArchivoSalida, const unordered_map<char, string>& pCodigos, const unordered_map<char, int>& pFrecuencias) 
{
    ofstream salida(pArchivoSalida, ios::binary);
    
    // Escribir el número de caracteres diferentes
    unsigned char numCaracteres = static_cast<unsigned char>(pFrecuencias.size());
    salida.write(reinterpret_cast<const char*>(&numCaracteres),1);
    
    // Escribir la tabla de frecuencias (char + int)
    uint32_t totalSimbolos =0;
    for (const auto& par : pFrecuencias) 
    {
        salida.put(par.first);
        int frecCodificada = par.second ^0xFF; // codificar (opcional)
        salida.write(reinterpret_cast<const char*>(&frecCodificada), sizeof(int));
        totalSimbolos += static_cast<uint32_t>(par.second);
    }

    // Escribir el tamaño original (número de símbolos) para poder decodificar correctamente
    salida.write(reinterpret_cast<const char*>(&totalSimbolos), sizeof(uint32_t));

    // Leer archivo de entrada y construir cadena de bits
    ifstream entrada(pArchivoEntrada, ios::binary);
    string cadenaBits;
    char caracter;
    while (entrada.get(caracter)) 
        cadenaBits += pCodigos.at(caracter);

    // Escribir los datos comprimidos (bits -> bytes)
    UtilidadesBit::escribirBitsEnArchivo(cadenaBits, salida);

    entrada.close();
    salida.close();
}

/*
* Descomprime un archivo utilizando el algoritmo de Huffman.
* Observación: Utiliza operaciones bit a bit para optimizar el proceso.
* @param:
*   - const string& pArchivoEntrada: Nombre del archivo de entrada.
*   - const string& pArchivoSalida: Nombre del archivo de salida.
* @return:
*   + void: No retorna valor.
*/
void Huffman::descomprimir(const string& pArchivoEntrada, const string& pArchivoSalida) 
{
    ifstream entrada(pArchivoEntrada, ios::binary);
    if (!entrada) return;

    unsigned char numCaracteres =0;
    entrada.read(reinterpret_cast<char*>(&numCaracteres),1);

    unordered_map<char, int> frecuencias;
    for (int i =0; i < numCaracteres; i++) 
    {
        char caracter;
        int frecuencia;
        entrada.get(caracter);
        entrada.read(reinterpret_cast<char*>(&frecuencia), sizeof(int));
        frecuencias[caracter] = frecuencia ^0xFF; // decodificar
    }

    // Leer tamaño original
    uint32_t totalSimbolos =0;
    entrada.read(reinterpret_cast<char*>(&totalSimbolos), sizeof(uint32_t));

    Nodo* raiz = construirArbol(frecuencias);

    // Leer el resto de los bytes comprimidos
    string bits;
    unsigned char byte;
    while (entrada.read(reinterpret_cast<char*>(&byte),1)) 
    {
        for (int i =7; i >=0; i--) 
            bits += (byte & (1 << i)) ? '1' : '0';
    }

    ofstream salida(pArchivoSalida, ios::binary);

    // Si el árbol tiene un solo símbolo, escribirlo totalSimbolos veces
    if (raiz && !raiz->izquierdo && !raiz->derecho) 
    {
        for (uint32_t i =0; i < totalSimbolos; ++i)
            salida.put(raiz->dato);
        entrada.close();
        salida.close();
        return;
    }

    // Decodificar usando el árbol y respetando totalSimbolos (para evitar bits de padding)
    Nodo* actual = raiz;
    uint32_t escritos =0;
    for (char bit : bits) 
    {
        if (bit == '0') actual = actual->izquierdo;
        else actual = actual->derecho;

        if (actual && actual->dato != '\0') 
        {
            salida.put(actual->dato);
            escritos++;
            if (escritos >= totalSimbolos) break;
            actual = raiz;
        }
    }

    entrada.close();
    salida.close();
}

/*
* Genera los códigos de Huffman a partir del árbol.
* Observación: Utiliza recursión para recorrer el árbol.
* @param:
*   - Nodo* pRaiz: Puntero a la raíz del árbol.
*   - string pCodigo: Código actual en construcción.
*   - unordered_map<char, string>& pCodigos: Mapa para almacenar los códigos.
* @return:
*   + void: No retorna valor.
*/
void Huffman::generarCodigos(Nodo* pRaiz, string pCodigo, unordered_map<char, string>& pCodigos)
{
    if (!pRaiz) return;
    
    // Si el árbol solo tiene un símbolo (raíz hoja) asignar un código "0"
    if (!pRaiz->izquierdo && !pRaiz->derecho) 
    {
        if (pCodigo.empty()) pCodigos[pRaiz->dato] = "0";
        else pCodigos[pRaiz->dato] = pCodigo;
        return;
    }
    
    if (pRaiz->dato != '\0')
        pCodigos[pRaiz->dato] = pCodigo;
  
    generarCodigos(pRaiz->izquierdo, pCodigo + "0", pCodigos);
    generarCodigos(pRaiz->derecho, pCodigo + "1", pCodigos);
}