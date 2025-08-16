#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


// Constantes
#define CARACTER 50
#define SIZE 50


// variables
int code[SIZE];
char names[SIZE][CARACTER];
int total = 0;


// Cadastrar produto
void storeProduct()
{
    setlocale(LC_ALL, "pt-BR");
    if (total < SIZE)
    {
        printf("Digite o codigo do produto: ");
        scanf("%d", &code[total]);
        getchar(); // consome ENTER

        printf("Digite o nome do produto: ");
        fgets(names[total], CARACTER, stdin);
        names[total][strcspn(names[total], "\n")] = 0; // remove \n

        total++;
        printf("Produto armazenado com sucesso!\n");
    }
    else
    {
        printf("Lista cheia!\n");
    }
}

// Ordenar produtos por codigo (Bubble Sort)
void sortProducts()
{
    setlocale(LC_ALL, "pt-BR");
    for (int i = 0; i < total - 1; i++)
    {
        for (int j = 0; j < total - i - 1; j++)
        {
            if (code[j] > code[j + 1])
            {
                int tempCod = code[j];
                code[j] = code[j + 1];
                code[j + 1] = tempCod;

                char tempName[CARACTER];
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);
            }
        }
    }
}

// Listar produtos
void listProducts()
{
    setlocale(LC_ALL, "pt-BR");
    if (total == 0)
    {
        printf("Nenhum produto cadastrado!\n");
        return;
    }

    sortProducts();
    printf("\n>>> Lista de produtos (ordenada por codigo) <<<\n");
    for (int i = 0; i < total; i++)
    {
        printf("codigo: %d | Nome: %s\n", code[i], names[i]);
    }
}

// Alterar produto
void changeProduct()
{
    setlocale(LC_ALL, "pt-BR");
    if (total == 0)
    {
        printf("Nenhum produto cadastrado!\n");
        return;
    }

    int codes;
    printf("Digite o codigo do produto que deseja alterar: ");
    scanf("%d", &codes);
    getchar();

    int found = 0;
    for (int i = 0; i < total; i++)
    {
        if (code[i] == codes)
        {
            printf("Digite o novo nome: ");
            fgets(names[i], CARACTER, stdin);
            names[i][strcspn(names[i], "\n")] = 0;
            printf("Produto alterado com sucesso!\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Produto não encontrado!\n");
    }
}

// Remover produto
void removeProduct()
{
    setlocale(LC_ALL, "pt-BR");
    if (total == 0)
    {
        printf("Nenhum produto cadastrado!\n");
        return;
    }

    int codes;
    printf("Digite o codigo do produto que deseja remover: ");
    scanf("%d", &codes);
    getchar();

    int found = 0;
    for (int i = 0; i < total; i++)
    {
        if (code[i] == codes)
        {
            for (int j = i; j < total - 1; j++)
            {
                code[j] = code[j + 1];
                strcpy(names[j], names[j + 1]);
            }
            total--;
            printf("Produto removido com sucesso!\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Produto não encontrado!\n");
    }
}

// Buscar produto por codigo (busca binária)
void searchProduct()
{
    setlocale(LC_ALL, "pt-BR");
    if (total == 0)
    {
        printf("Nenhum produto cadastrado!\n");
        return;
    }

    int codes;
    printf("Digite o codigo do produto que deseja buscar: ");
    scanf("%d", &codes);
    getchar();

    sortProducts();
    int start = 0, end = total - 1, quite;
    int found = 0;

    while (start <= end)
    {
        quite = (start + end) / 2;
        printf("Verificando caixa com codigo %d...\n", code[quite]);

        if (code[quite] == codes)
        {
            printf("Produto encontrado: %s (codigo %d)\n", names[quite], code[quite]);
            found = 1;
            break;
        }
        else if (codes < code[quite])
        {
            end = quite - 1;
        }
        else
        {
            start = quite + 1;
        }
    }

    if (!found)
    {
        printf("Produto não encontrado!\n");
    }
}

int main()
{
    setlocale(LC_ALL, "pt-BR");

    int option;
    do
    {
        printf("\n============================\n");
        printf("       MENU DE PRODUTOS     \n");
        printf("============================\n");
        printf("1 - Armazenar Produto\n");
        printf("2 - Alterar Produto\n");
        printf("3 - Remover Produto\n");
        printf("4 - Listar Produtos\n");
        printf("5 - Buscar Produto por Codigo\n");
        printf("0 - Sair\n");
        printf("============================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &option) != 1)
        {
            printf("Entrada inválida! Digite apenas números.\n");
            while (getchar() != '\n')
                ;
            option = -1;
            continue;
        }
        getchar();

        switch (option)
        {
        case 1:
            storeProduct();
            break;
        case 2:
            changeProduct();
            break;
        case 3:
            removeProduct();
            break;
        case 4:
            listProducts();
            break;
        case 5:
            searchProduct();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }

    } while (option != 0);


}
