// Para mais informações consulte o REDME.md do projeto
#include "ARVORE_PREFIXO.H"

ARVORE_PREFIXO::ARVORE_PREFIXO()
{
    root = NULL;
}

void ARVORE_PREFIXO::DeleteTree(ARVORE_PREFIXO_POINTER node)
{
    if (node->Entry != '*')
    {
        delete node;
    }
    else
    {
        DeleteTree(node->LeftNode);
        DeleteTree(node->RightNode);
        delete node;
    }
}

ARVORE_PREFIXO::~ARVORE_PREFIXO()
{
    DeleteTree(root);
}

void ARVORE_PREFIXO::ConvertStringToNode(string str)
{
    root = new struct ARVORE_PREFIXO_NODE;
    ConvertStringToNode(str, root);
}

void ARVORE_PREFIXO::Print()
{
    Print(root, 0);
}

void ARVORE_PREFIXO::ConvertStringToNode(string str, ARVORE_PREFIXO_POINTER node)
{
    if (str[indice] == '*')
    {
        node->LeftNode = new struct ARVORE_PREFIXO_NODE;
        indice++;
        ConvertStringToNode(str, node->LeftNode);
        node->RightNode = new struct ARVORE_PREFIXO_NODE;
        indice++;
        ConvertStringToNode(str, node->RightNode);
    }
    else
    {
        node->Entry = str[indice];
    }
}

void ARVORE_PREFIXO::Print(ARVORE_PREFIXO_POINTER node, int s)
{
    int i;
    if (node != NULL)
    {
        Print(node->LeftNode, s + 3);
        for (i = 1; i <= s; i++)
            cout << " ";

        cout << setw(3) << (char)node->Entry << endl;

        Print(node->RightNode, s + 3);
    }
}

void ARVORE_PREFIXO::PrintTable()
{
    PrintTable(root, 0, " ", " ");
}

void ARVORE_PREFIXO::PrintTable(ARVORE_PREFIXO_POINTER node, int bits, string path, string partPath)
{
    path = path.append(partPath);
    if (node->Entry == '*')
    {
        PrintTable(node->LeftNode, bits + 1, path, "0");
        PrintTable(node->RightNode, bits + 1, path, "1");
    }
    else
    {
        cout << node->Entry;
        cout << setw(6) << bits;
        cout << setw(6) << path << endl;
    }
}

void ARVORE_PREFIXO::Uncompressed(string messageCompressed)
{
    indice = 0;
    Uncompressed(root, messageCompressed);
    cout << messageDescompressed << endl;
    cout << "Quantidade de bits = " << StrLength(messageCompressed) << endl;
    cout << "Numero de caracteres = " << StrLength(messageDescompressed) << endl;
    cout.precision(10);
    cout << "Taxa de compressao = " << SizeCompression(messageCompressed, messageDescompressed) << "%" << endl;
}

void ARVORE_PREFIXO::Uncompressed(ARVORE_PREFIXO_POINTER node, string message)
{
    if (node->Entry != '*')
    {
        messageDescompressed.push_back(node->Entry);

        if (message[indice] == '\0')
            return;

        Uncompressed(root, message);
    }
    else
    {
        if (message[indice] == '0')
        {
            indice++;
            Uncompressed(node->LeftNode, message);
        }
        else if (message[indice] == '1')
        {
            indice++;
            Uncompressed(node->RightNode, message);
        }
    }
}

int ARVORE_PREFIXO::StrLength(string message)
{
    int size = 0;
    while (message[size++] != '\0');
    return size - 1;
}

long double ARVORE_PREFIXO::SizeCompression(string compressed, string uncompressed)
{
    return ((long double)StrLength(compressed) * 100) / ((long double)StrLength(uncompressed) * 8);
}