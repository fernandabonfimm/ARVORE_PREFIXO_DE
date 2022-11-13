// Para mais informações consulte o REDME.md do projeto
#include "ARVORE_PREFIXO.H"

// argv e argc são como os argumentos de linha de comando são passados ​​para main() em C++.
int main(int argc, char **argv)
{
  setlocale(LC_ALL, "Portuguese");
  // A variavel de tipo classe 'tree' sera responsavel por chamar nossas funções
  ARVORE_PREFIXO tree;
  // Pedimos para que o argc informe um arquivo para o mesmo ser aberto e rodado pelo argv
  if (argc < 2)
  {
    cout << "Informe um arquivo" << endl;
    cout << "Exemplo: ./out nome_do_aquivo" << endl;
    // caso nao informar nenhum arquivo o programa irá ser abortado
    abort();
  }
  // Definimos que o argv vai ler primeiramente 1, pois é o arquivo que será passado, caso definirmos 0, irá ler o nosso próprio pois conta como arquivo
  ifstream file(argv[1], ios::in);
  // Definimos nossa string de representação da arvore e de mensagem, para os parametros do getline e funções
  string treeRepresentation, messageCompressed;

  // Se o usuário informar um arquivo que nao existe dentro do projeto, iremos informar que não é possivel no terminal e abortaremos o programa
  if (!file.is_open())
  {
    cout << "Arquivo nao existe dentro do projeto!" << endl;
    abort();
  }

  // Utilizamos o getline para ler o arquivo.pre escolhido pelo usuário, e para isso passamos nosso file e o tipo de string de leitura
  getline(file, treeRepresentation);
  getline(file, messageCompressed);

  // Imprimimos nossa árvore, que permanece com a mesma estrutura solicitada no pdf, independente do arquivo.pre
  cout << "       Arvore     " << endl;
  cout << "------------------" << endl;
  // Primeiro é necessario converter nossa string para node, para assim podermos construir e imprimir nossa árvore
  tree.ConvertStringToNode(treeRepresentation);
  // Função que chama a árvore impressa
  tree.Print();
  cout << "\n\n"
       << endl;
  // Imprimimos nossa tabela de bits, caracter e codificação
  cout << "      Tabela     " << endl;
  cout << "-----------------" << endl;
  tree.PrintTable();
  cout << endl;
  // Chamamos nossa função que descomprime a mensagem e imprimimos na tela
    cout << "\n\n"
       << endl;
  cout << "      Descomprimindo     " << endl;
  cout << "-------------------------" << endl;
  tree.Uncompressed(messageCompressed);

  file.close();
  return 0;
}