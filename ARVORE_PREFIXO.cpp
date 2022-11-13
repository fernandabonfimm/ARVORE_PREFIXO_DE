// Para mais informações consulte o REDME.md do projeto
#include "ARVORE_PREFIXO.H"

ARVORE_PREFIXO::ARVORE_PREFIXO()
{
    // Inicamos nossa árvore definindo que o nó seria nulo
    root = NULL;
}

void ARVORE_PREFIXO::DeleteTree(ARVORE_PREFIXO_POINTER node)
{
    // Verificamos se os nós são diferentes de * na árvore
    if (node->Entry != '*')
    {
        // Caso sejam, deletamos
        delete node;
    }
    else
    {
        // Caso não sejam, devemos deletar nó por nó, da esquerda para a direita
        DeleteTree(node->LeftNode);
        DeleteTree(node->RightNode);
        delete node;
    }
}

ARVORE_PREFIXO::~ARVORE_PREFIXO()
{
    // Chamamos noss função que deleta os nós da árvore em nosso destrutor e passamos nossa raiz para destrui-lá
    DeleteTree(root);
}

void ARVORE_PREFIXO::ConvertStringToNode(string str)
{
    // Para converter a string para nó em modo público, definimos que nossa raiz irá receber um novo nó
    // E chamamos nossa função, passando como parametro a nossa string e a nova raiz
    root = new struct ARVORE_PREFIXO_NODE;
    ConvertStringToNode(str, root);
}

void ARVORE_PREFIXO::Print()
{
    // Para imprimir a árvore, basta chamar a função abaixo e definir como paramêtro a raiz e o elemento 0
    Print(root, 0);
}

void ARVORE_PREFIXO::ConvertStringToNode(string str, ARVORE_PREFIXO_POINTER node)
{
    // Nesta função é onde nós realmente convertemos nossa string em nó, pois precisamos passar como paramêtro nosso ARVORE_PREFIXO_POINTER que é privado
    // Se nossa string que recebo indice for igual a *
    if (str[indice] == '*')
    {
        // Nosso nó irá receber os nós à esquerda da árvore, e irá definir um novo nó
        node->LeftNode = new struct ARVORE_PREFIXO_NODE;
        indice++;
        ConvertStringToNode(str, node->LeftNode);
        // Nosso nó irá receber os nós à direita da árvore, e irá definir um novo nó
        node->RightNode = new struct ARVORE_PREFIXO_NODE;
        indice++;
        ConvertStringToNode(str, node->RightNode);
    }
    else
    {
        node->Entry = str[indice];
    }
}

// Função que irá contruir e printar a árvore na tela do usuário
void ARVORE_PREFIXO::Print(ARVORE_PREFIXO_POINTER node, int s)
{
    int i;

    // se o nó for diferente de nulo receberá a função Print com o node apontando LeftNode
    if (node != NULL)
    {
        // Desta forma a árvore será contruída na forma Pré-Ordem como foi determinado no enunciado
        Print(node->LeftNode, s + 3);
        for (i = 1; i <= s; i++)
            cout << " ";

        // inserindo os elementos na árvore
        cout << setw(3) << (char)node->Entry << endl;

        // Após iniciar pela esquerda a inserção será pela direita
        Print(node->RightNode, s + 3);
    }
}

// Função para receber uma função no modo private da classe
void ARVORE_PREFIXO::PrintTable()
{
    PrintTable(root, 0, " ", " ");
}

// Função que irá montar e mostrar a tabela com as colunas de caractere e codificação
void ARVORE_PREFIXO::PrintTable(ARVORE_PREFIXO_POINTER node, int bits, string path, string partPath)
{
    // utilizamos essa estrutura para acrescentar caracteres no final da string
    path = path.append(partPath);

    // Nó vai receber uma entrada e se ela for igual ao caracter * vai retornar a tabela preenchida com o numero de bits desse caractere
    if (node->Entry == '*')
    {
        // printando pela esquerda e somando um ao bit, no final a string path será acrescentada um "0"
        PrintTable(node->LeftNode, bits + 1, path, "0");
        // printando pela direita e somando um ao bit, no final a string path será acrescentada um "1"
        PrintTable(node->RightNode, bits + 1, path, "1");
    }
    else
    {
        // caso contrário será printado na tela a o elemento e seu codificação
        cout << node->Entry;
        cout << setw(6) << bits;
        cout << setw(6) << path << endl;
    }
}

void ARVORE_PREFIXO::Uncompressed(string messageCompressed)
{
    // Nossa função pública que chamamos a nossa privada que realmente faz a descompressão da mensagem e imprimimos o resultado
    indice = 0;
    // Passamos como parametro para realizar a descompressão da mensagem, nossa raiz e a nossa string
    Uncompressed(root, messageCompressed);
    cout << messageDescompressed << endl;
    // Mostramos a quantidade de bits com a função de calculamos o tamanho da nossa string
    cout << "Quantidade de bits = " << StrLength(messageCompressed) << endl;
    // E mostramos também o numero de caracteres dessa string
    cout << "Numero de caracteres = " << StrLength(messageDescompressed) << endl;
    // Utilizamos o precision para imprimir nosso valor, pois o mesmo está duplicado, para que a taxa de compreensão fique exatamente igual mostrado no pdf
    cout.precision(10);
    // Mostramos nossa taxa exata de compressão chamando nossa função que faz o calculo da taxa, passando como parametro a string comprimida e descomprimida
    cout << "Taxa de compressao = " << SizeCompression(messageCompressed, messageDescompressed) << "%" << endl;
}

// Função que irá descomprimir a mensagem
void ARVORE_PREFIXO::Uncompressed(ARVORE_PREFIXO_POINTER node, string message)
{
    // caso a entrada do elemento seja um "*"
    if (node->Entry != '*')
    {
        // recebe a string messageDescompressed e será inserida no final do vetor
        messageDescompressed.push_back(node->Entry);

        // irá retornar a função uncompressed se a string mesage contendo o indice for igual ao final da string
        if (message[indice] == '\0')
            return;

        Uncompressed(root, message);
    }
    else
    {
        // Caso contrário, nossa mensagem recebera nosso indice em array e verificará se é igual a 0
        if (message[indice] == '0')
        {
            indice++;
            Uncompressed(node->LeftNode, message);
            // Realizamos o indice++, para que percora na árvore e que descomprime a mesma da parte esquerda a direita
            // Chamamos nossa função para o mesmo e passamos nossos nó e mensagem, para realizar o tal.
        }
        else if (message[indice] == '1')
        {
            // Se nossa mensagem por igual a 1
            indice++;
            Uncompressed(node->RightNode, message);
            // Realizamos o mesmo do lado direito da árvore
        }
    }
}

int ARVORE_PREFIXO::StrLength(string message)
{
    // Para sabermos o tamanho da nossa string, precisamos de uma estrutura de repetição de jogue o tamanho para dentro de um array e faça até que seja diferente de '/0'
    int size = 0;
    while (message[size++] != '\0')
        ;
    // Retornamos o size - 1, pois estava contando um mais dentro da nossa estrutura de repetição
    return size - 1;
}

long double ARVORE_PREFIXO::SizeCompression(string compressed, string uncompressed)
{
    // Utilizamos a função do tipo long double, por que, refere-se a um tipo de dados de ponto flutuante que geralmente é mais preciso que a precisão dupla.
    // Para realizar o calculo da taxa de compreensão precisamos forçar as funções de StrLenght a ser do tipo long double
    // 1° chamada da StrLenght: passamos como parametro a string do arquivo comprimido e multiplicamos por 100
    // 1° chamada da StrLenght: passamos como parametro a string do arquivo descomprimido e multiplicamos por 8
    // Depois dividimos ambas e retornamos o resultado
    return ((long double)StrLength(compressed) * 100) / ((long double)StrLength(uncompressed) * 8);
}