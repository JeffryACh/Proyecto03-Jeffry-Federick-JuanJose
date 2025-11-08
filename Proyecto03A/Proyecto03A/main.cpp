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
#include <queue>
#include <unordered_map>

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
void decode(Node* raiz, int& index, string str) {
	if (raiz == nullptr) 
		return;
	
	if (!raiz->izq && !raiz->der) {
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
* Crea el arbol de Huffman y decodifocas dados los simbolos
* Observación: Construye el árbol de Huffman a partir de la frecuencia de los símbolos en el texto.
* @param:
*	- string text: Texto a comprimir y descomprimir.
* @return:
*	+ void: No retorna valor.
*/
void CrearArbol(string text) 
{
	// Cuenta la cantidad de veces que aparece cada simbolo y la guarda en el mapa
	unordered_map<char, int> frecuencia;
	for (char simbolo : text) 
		frecuencia[simbolo]++;
	
	// Crea una cola de prioridad para guardar los nodos del arbol
	priority_queue<Node*, vector<Node*>, comp> pq;
	// Agrega a la cola de prioridad los nodos de cada simbolo
	for (auto pair : frecuencia) 
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));

	// Hacer todo el proceso hasta que haya mas de 1 nodo en la cola
	while (pq.size() != 1) 
	{
		Node* izq = pq.top(); pq.pop();
		Node* der = pq.top(); pq.pop();
		int sum = izq->frecuencia + der->frecuencia;
		pq.push(getNode('\0', sum, izq, der));
	}

	Node* raiz = pq.top();
	// Imprime los codigos para cada simbolo
	unordered_map<char, string> CodigoHuffman;
	encode(raiz, "", CodigoHuffman);
	cout << "\nLos codigos de Huffman son:\n" << "\n";
	for (auto pair : CodigoHuffman) 
		cout << pair.first << " " << pair.second << '\n';

	// Imprime el mensaje original que el usuario ingreso directamente, el codificado
	// y decodifica el codificado y lo imprime de nuevo
	cout << "\nEl mensaje original era:\n" << text << '\n';
	string str = "";
	for (char simbolo : text) 
		str += CodigoHuffman[simbolo];
	
	cout << "\nEl texto codificado es: \n" << str << '\n';
	int index = -1;
	cout << "\nEl texto decodificado es: \n";
	while (index < (int)str.size() - 1)
		decode(raiz, index, str);
	cout << "\n\n\n";
}

int main() 
{
	cout << "\n\n\n-----------------------------";
	cout << "\n Compresion y Descompresion con el metodo de Huffman";

	string text;
	cout << "\n\nIngrese el mensaje que desea comprimir: ";
	getline(cin, text);
	CrearArbol(text);
	cout << "\n";
	return 0;

}