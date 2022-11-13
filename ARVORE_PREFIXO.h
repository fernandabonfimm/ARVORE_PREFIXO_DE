// Para mais informações consulte o REDME.md do projeto
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <locale.h>
#include <time.h>
#include <fstream>

using namespace std;
using std::getline;

// Antes de iniciarmos nossa documentação sobre o projeto, é importante salientar
// que o código inteiro foi feito baseado na árvore de Huffman e foi feito com recursão, para tornar maior a compreensão do mesmo.

// Como foi solicitado no PDF, nossa classe, struct e ponteiros, segue o nome de ARVORE_PREFIXO
class ARVORE_PREFIXO
{
  // Funções publicas
public:
  // Função responsável por criar nossa árvore
  ARVORE_PREFIXO();
  // Função responsável por destruir nossa árvore
  ~ARVORE_PREFIXO();
  // Função recursiva pública que contribui para a função de mesmo nome privada com os nós definidos, que converte a string para nó na árvore
  void ConvertStringToNode(string str);
  // Função recursiva pública que contribui para a função de mesmo nome privada com os nós definidos, que nos mostra nossa árvore
  void Print();
  // Função recursiva pública que contribui para a função de mesmo nome privada com os nós definidos, que monta e nos mostra nossa tabela
  void PrintTable();
  // Função recursiva pública que contribui para a função de mesmo nome privada com os nós definidos, que descomprime a mensagem
  void Uncompressed(string messageCompressed);

  // Funções e variaveis privadas
private:
  // Struct que utilizamos para definir nossos nós de direita e esquerda além da raiz
  struct ARVORE_PREFIXO_NODE
  {
    // Utilizamos char em nosso Entry pois estamos trabalhando com strings
    char Entry = '*';
    ARVORE_PREFIXO_NODE *LeftNode = NULL, *RightNode = NULL;
  };
  typedef ARVORE_PREFIXO_NODE *ARVORE_PREFIXO_POINTER;

  ARVORE_PREFIXO_POINTER root;
  int indice = 0;
  // Definimos que as mensagem passariam a ser string para facilitar o getline dos arquivos
  string messageDescompressed;

  // Função privada que transforma string em nó
  void ConvertStringToNode(string str, ARVORE_PREFIXO_POINTER node);
  // Função privada que constroi e imprime nossa árvore binária
  void Print(ARVORE_PREFIXO_POINTER node, int s);
  // Função privada que constroi e imprime nossa tabel
  void PrintTable(ARVORE_PREFIXO_POINTER node, int bits, string path, string partPath);
  // Função privada que descomprime a mensagem comprimida
  void Uncompressed(ARVORE_PREFIXO_POINTER node, string message);
  // Função privada que irá calcular e imprimir o tamanho da string da mensagem
  int StrLength(string message);
  // Função privada calcula e imprime o tamanho da mensagem, utilizando a string da mesma comprimida e descomprimida
  long double SizeCompression(string compressed, string uncompressed);
  // Função privada que deleta os nós da árvore que depois utilizamos para destruir em nosso destrutor
  void DeleteTree(ARVORE_PREFIXO_POINTER node);
};