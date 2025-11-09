/*
* Proyecto 03A: Compresor y descompresor Huffman
* @Authors:
*   - Jeffry Araya Ch.
*   - Federick Fernandez C.
*   - Juan J. Rojas
*
* Created: 07/11/2025 10:50
* Modified: 08/11/2025 18:40
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <queue>
#include <unordered_map>
#include <fstream>

using namespace std;

/*
* Nodo del arbol
* Observación: Estructura utilizada para representar cada nodo en el árbol de Huffman.
* @attributes:
*	- char simbolo: Caracter almacenado en el nodo.
*	- int frecuencia: Frecuencia del caracter.
*	- Node* izq: Puntero al hijo izquierdo.
*   - Node* der: Puntero al hijo derecho.
*/ 
struct Node 
{
	char simbolo;
	int frecuencia;
	Node* izq, * der;
};

/*
* Funcion para asignar un nuevo nodo en el arbol
* Observación: Crea y retorna un nuevo nodo con los valores proporcionados.
* @param:
*	- char simbolo: Caracter a almacenar en el nodo.
* 	- int frecuencia: Frecuencia del caracter.
*   - Node* izq: Puntero al hijo izquierdo.
*   - Node* der: Puntero al hijo derecho.
* @return:
*	+ Node*: Puntero al nuevo nodo creado.
*/ 
Node* getNode(char simbolo, int frecuencia, Node* izq, Node* der) 
{
	Node* nodo = new Node();

	nodo->simbolo = simbolo;
	nodo->frecuencia = frecuencia;
	nodo->izq = izq;
	nodo->der = der;

	return nodo;
}

/*
* Objeto de comparacion que será usado para ordenar la pila
* Observación: Define el criterio de comparación para la prioridad en la cola.
* @attributes:
*	- bool operator() (Node* i, Node* d): Sobrecarga del operador para comparar dos nodos.
*/ 
struct comp
{
	bool operator() (Node* i, Node* d)
	{
		return i->frecuencia > d->frecuencia;
	}
};

/*
* Revisa el arbol de Huffman y guarda los códigos en un mapa
* Observación: Realiza un recorrido del árbol para generar los códigos de Huffman.
* @param:
*	- Node* raiz: Puntero a la raíz del árbol de Huffman.
*   - string str: Cadena que representa el código actual.
*   - unordered_map<char, string>& CodigoHuffman: Mapa para almacenar los códigos generados.
* @return:
*	+ void: No retorna valor.
*/
void encode(Node* raiz, string str, unordered_map<char, string>& CodigoHuffman) 
{
	if (raiz == nullptr)
		return;
	if (!raiz->izq && !raiz->der) 
		CodigoHuffman[raiz->simbolo] = str;

	encode(raiz->izq, str + "0", CodigoHuffman);
	encode(raiz->der, str + "1", CodigoHuffman);
}

/*
* Revisa el arbol y decodifica los simbolos codificados
* Observación: Realiza un recorrido del árbol para decodificar una cadena de bits.
* @param:
*	- Node* raiz: Puntero a la raíz del árbol de Huffman.
*   - int& index: Índice actual en la cadena de bits.
*   - string str: Cadena de bits a decodificar.
* @return:
*	+ void: No retorna valor.
*/
void decode(Node* raiz, int& index, string str) 
{
	if (raiz == nullptr) 
		return;
	
	if (!raiz->izq && !raiz->der) 
	{
		cout << raiz->simbolo;
		return;
	}
	index++;
	if (str[index] == '0')
		decode(raiz->izq, index, str);
	else
		decode(raiz->der, index, str);
}

/*
* Crea el arbol de Huffman y comprime un archivo
* Observación: Lee un archivo, construye el árbol de Huffman y crea un archivo comprimido.
* @param:
*	- string inputFile: Nombre del archivo a comprimir.
*   - string outputFile: Nombre del archivo comprimido.
* @return:
*	+ void: No retorna valor.
*/
void CrearArbolArchivo(const string& inputFile, const string& outputFile) {
	ifstream in(inputFile, ios::binary);
	if (!in) 
	{
		cerr << "Error al abrir el archivo para comprimir." << endl;
		return;
	}

	unordered_map<char, int> frecuencia; // Cambiando a char para compatibilidad con encode
	char ch;
	while (in.get(ch)) 
		frecuencia[ch]++;
	

	priority_queue<Node*, vector<Node*>, comp> pq;
	for (auto pair : frecuencia) 
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	

	while (pq.size() !=1)
	{
		Node* izq = pq.top(); pq.pop();
		Node* der = pq.top(); pq.pop();
		int sum = izq->frecuencia + der->frecuencia;
		pq.push(getNode('\0', sum, izq, der));
	}

	Node* raiz = pq.top();
	unordered_map<char, string> CodigoHuffman; // Cambiando a char para compatibilidad con encode
	encode(raiz, "", CodigoHuffman);

	in.clear();
	in.seekg(0);
	ofstream out(outputFile, ios::binary);
	if (!out) 
	{
		cerr << "Error al crear el archivo comprimido." << endl;
		return;
	}

	size_t mapSize = CodigoHuffman.size();
	out.write(reinterpret_cast<const char*>(&mapSize), sizeof(size_t));
	for (auto pair : CodigoHuffman) 
	{
		out.put(pair.first);
		size_t len = pair.second.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
		out.write(pair.second.c_str(), len);
	}

	while (in.get(ch)) 
	{
		string code = CodigoHuffman[ch];
		for (char bit : code) 
			out.put(bit);
		
	}

	in.close();
	out.close();
	cout << "Archivo comprimido correctamente: " << outputFile << endl;
}

/*
* Descomprime un archivo utilizando el método de Huffman
* Observación: Lee un archivo comprimido y lo descomprime utilizando el árbol de Huffman.
* @param:
*	- string inputFile: Nombre del archivo comprimido.
*   - string outputFile: Nombre del archivo descomprimido.
* @return:
*	+ void: No retorna valor.
*/
void DescomprimirArchivo(const string& inputFile, const string& outputFile)
{
	ifstream in(inputFile, ios::binary);
	if (!in) 
	{
		cerr << "Error al abrir el archivo comprimido." << endl;
		return;
	}

	size_t mapSize;
	in.read(reinterpret_cast<char*>(&mapSize), sizeof(size_t));
	unordered_map<string, char> CodigoHuffman; // Cambiando a char para compatibilidad
	for (size_t i =0; i < mapSize; ++i) 
	{
		char simbolo = in.get();
		size_t len;
		in.read(reinterpret_cast<char*>(&len), sizeof(size_t));
		string code(len, '\0');
		in.read(&code[0], len);
		CodigoHuffman[code] = simbolo;
	}

	ofstream out(outputFile, ios::binary);
	if (!out) 
	{
		cerr << "Error al crear el archivo descomprimido." << endl;
		return;
	}

	string buffer;
	char bit;
	while (in.get(bit)) 
	{
		buffer += bit;
		if (CodigoHuffman.find(buffer) != CodigoHuffman.end()) 
		{
			out.put(CodigoHuffman[buffer]);
			buffer.clear();
		}
	}

	in.close();
	out.close();
	cout << "Archivo descomprimido correctamente: " << outputFile << endl;
}

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
	string opcion;

	// Menú principal
	// Observación: Permite al usuario seleccionar entre comprimir, descomprimir o salir del programa.
	// Utiliza un bucle while para mantener el menú activo hasta que el usuario decida salir.
	// Valida la entrada del usuario y llama a las funciones correspondientes según la opción seleccionada.
	// Solicita al usuario los nombres de los archivos de entrada y salida para las operaciones de compresión y descompresión.
	// Muestra mensajes informativos sobre el estado de las operaciones realizadas.
	while (convertirMinusculas(opcion) != "s")
	{
		cout << "\n\n\n-----------------------------";
		cout << "\n Compresion y Descompresion con el metodo de Huffman";
		cout << "\n\nSeleccione una opción: (c) Comprimir, (d) Descomprimir, (s) Salir: ";
		cin >> opcion;

		if (convertirMinusculas(opcion) != "c" && convertirMinusculas(opcion) != "d" && convertirMinusculas(opcion) != "s")
		{
			cout << "Opción no válida. Intente de nuevo." << endl;
			continue;
		}
		else if (convertirMinusculas(opcion) == "c")
			cout << "\nHa seleccionado la opción de Comprimir un archivo." << endl;
		else if (convertirMinusculas(opcion) == "d")
			cout << "\nHa seleccionado la opción de Descomprimir un archivo." << endl;
		else if (convertirMinusculas(opcion) == "s")
		{
			cout << "Saliendo del Menu." << endl;
			break;
		}

		string inputFile, outputFile;
		cout << "\nIngrese el archivo de entrada: ";
		cin >> inputFile;
		cout << "\nIngrese el archivo de salida: ";
		cin >> outputFile;
	
	
		if (convertirMinusculas(opcion) == "c")
			CrearArbolArchivo(inputFile, outputFile);
		else
			DescomprimirArchivo(inputFile, outputFile);
	}
	

	return 0;
}