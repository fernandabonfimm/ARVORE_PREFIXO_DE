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

class ARVORE_PREFIXO
{
public:
  ARVORE_PREFIXO();
  ~ARVORE_PREFIXO();
  void ConvertStringToNode(string str);
  void Print();
  void PrintTable();
  void Uncompressed(string messageCompressed);

private:
  struct ARVORE_PREFIXO_NODE
  {
    char Entry = '*';
    ARVORE_PREFIXO_NODE *LeftNode = NULL, *RightNode = NULL;
  };
  typedef ARVORE_PREFIXO_NODE *ARVORE_PREFIXO_POINTER;

  ARVORE_PREFIXO_POINTER root;
  int indice = 0;
  string messageDescompressed;
  void ConvertStringToNode(string str, ARVORE_PREFIXO_POINTER node);
  void Print(ARVORE_PREFIXO_POINTER node, int s);
  void PrintTable(ARVORE_PREFIXO_POINTER node, int bits, string path, string partPath);

  void Uncompressed(ARVORE_PREFIXO_POINTER node, string message);
  int StrLength(string message);
  long double SizeCompression(string compressed, string uncompressed);
  void DeleteTree(ARVORE_PREFIXO_POINTER node);
};