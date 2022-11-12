// Para mais informações consulte o REDME.md do projeto
#include "ARVORE_PREFIXO.H"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "Portuguese");
    ARVORE_PREFIXO tree;
    if (argc < 2) {
      cout << "Informe um arquivo" << endl;
      cout << "Exemplo: ./out nome_do_aquivo" << endl;
      abort();
    }
    ifstream file(argv[1], ios::in);
    string treeRepresentation, messageCompressed;

    if (!file.is_open()) {
      cout << "Arquivo nao existe dentro do projeto!" << endl;
      abort();
    } 

    getline(file, treeRepresentation);
    getline(file, messageCompressed);

    cout << "\n\n" << endl;
    cout << "       Arvore     " << endl;
    cout << "------------------" << endl;
    tree.ConvertStringToNode(treeRepresentation);
    tree.Print();
    cout << "\n\n" << endl;
    cout << "      Tabela     " << endl;
    cout << "-----------------" << endl;
    tree.PrintTable();
    cout << endl;
    tree.Uncompressed(messageCompressed);

    file.close();
    return 0;
}