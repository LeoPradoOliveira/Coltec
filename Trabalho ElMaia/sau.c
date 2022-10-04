#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_INGREDIENTE 50 + 1
#define TAM_MAX_RECEITA 100 + 1
#define SUCESSO 0

typedef struct
{
    int quantidade_ingredientes;
    int *quantidade_do_ingrediente;
    int *ingredientes;
    char *nome_receita;
} receita;

typedef struct
{
    char *ingrediente;
} ingrediente;

int numero_receitas(FILE *arq){
    int aux = 0;
    if ((arq = fopen("Receitas.txt", "r")) == NULL)
    {
        printf("Impossivel abrir o arquivo em numero_receitas\n");
        exit(1);
    }

    char texto[TAM_MAX_RECEITA];

    while (fgets(texto, TAM_MAX_RECEITA, arq) != NULL)
        aux++;

    fclose(arq);
    return aux;
}

void verificar_ingredientes(FILE *arq){
    if ((arq = fopen("Ingredientes.txt", "a+")) == NULL)
    {
        printf("Impossivel abrir o arquivo em verificar_ingredientes\n");
        exit(1);
    }

    if (fgetc(arq) == EOF)
        fprintf(arq, "Farinha\nFermento\nMussarela\nMolho de Tomate\nTomate\nOregano\nCebola\nAzeitona\nCatupiry\nCalabresa\nAlho\nManjericao\nRequeijao\nFrango\nPepperoni\nPresunto\nBacon\nPimentao\nChampignon\nProvolone\n");
    fclose(arq);
}

void cadastrar_ingrediente(FILE *arq){
    verificar_ingredientes(arq);
    if ((arq = fopen("Ingredientes.txt", "a")) == NULL)
    {
        printf("Impossivel abrir o arquivo em cadastrar_ingrediente\n");
        exit(1);
    }

    ingrediente proximo;

    proximo.ingrediente = (char *)calloc(TAM_MAX_INGREDIENTE, sizeof(char));

    printf("Informe o ingrediente que queira cadastrar: \n");
    fflush(stdin);
    fgets(proximo.ingrediente, TAM_MAX_INGREDIENTE, stdin);
    proximo.ingrediente[strlen(proximo.ingrediente) - 1] = '\0';

    fprintf(arq, "%s\n", proximo.ingrediente);
    fclose(arq);
}

int numero_ingredientes(FILE *arq){
    int aux = 0;
    if ((arq = fopen("Ingredientes.txt", "r")) == NULL)
    {
        printf("Impossivel abrir o arquivo em numero_ingredientes\n");
        exit(1);
    }
    char texto[TAM_MAX_INGREDIENTE];

    while (fgets(texto, TAM_MAX_INGREDIENTE, arq) != NULL)
        aux++;

    fclose(arq);
    return aux;
}

void listar_por_descricao(FILE *arq){
    int i, j, k;
    char *tmp;

    if ((arq = fopen("Ingredientes.txt", "r")) == NULL)
    {
        printf("Impossivel abrir o arquivo em listar_por_descricao\n");
        exit(1);
    }

    int num_ingredientes = numero_ingredientes(arq);

    char **vetorStrings;

    if ((vetorStrings = (char **)malloc(sizeof(char *) * num_ingredientes)) == NULL)
    {
        printf("Erro alocacao de memoria em listar_por_descricao\n");
        exit(1);
    }

    for (i = 0; i < num_ingredientes; i++)
    {
        vetorStrings[i] = (char *)malloc(sizeof(char) * TAM_MAX_INGREDIENTE);
        if (vetorStrings[i] == NULL)
        {
            printf("Erro alocacao de memoria em listar_por_descricao\n");
            exit(1);
        }
    }

    for (i = 0; i < num_ingredientes; i++)
    {
        fgets(vetorStrings[i], TAM_MAX_INGREDIENTE, arq);
        vetorStrings[i][strlen(vetorStrings[i]) - 1] = '\0';
    }

    for (i = 0; i < num_ingredientes - 1; i++)
    {
        for (j = 0; j < num_ingredientes - 1; j++)
        {
            // Se estiver fora de ordem...
            if (strcmp(vetorStrings[j], vetorStrings[j + 1]) > 0)
            {
                // ... troca de posicao
                tmp = vetorStrings[j];
                vetorStrings[j] = vetorStrings[j + 1];
                vetorStrings[j + 1] = tmp;
            }
        }
    }

    for (i = 0; i < num_ingredientes; i++)
    {
        fseek(arq, 0, SEEK_SET);

        for (k = 0; k < num_ingredientes; k++)
        {
            char texto[TAM_MAX_INGREDIENTE];

            fgets(texto, TAM_MAX_INGREDIENTE, arq);
            texto[strlen(texto) - 1] = '\0';

            if (strcmp(texto, vetorStrings[i]) == 0)
                printf("%d ", k + 1);
        }

        printf("%s\n", vetorStrings[i]);
    }

    for (i = 0; i < num_ingredientes; i++)
        free(vetorStrings[i]);

    free(vetorStrings);

    fclose(arq);
}

void listar_por_codigo(FILE *arq){
    int i;

    if ((arq = fopen("Ingredientes.txt", "r")) == NULL)
    {
        printf("Impossivel abrir o arquivo em listar_por_codigo\n");
        exit(1);
    }

    int num_ingredientes = numero_ingredientes(arq);

    char vetorStrings[num_ingredientes][TAM_MAX_INGREDIENTE];

    for (i = 0; i < num_ingredientes; i++)
    {
        fgets(vetorStrings[i], TAM_MAX_INGREDIENTE, arq);
        if (vetorStrings[i][strlen(vetorStrings[i]) - 1] == '\n')
            vetorStrings[i][strlen(vetorStrings[i]) - 1] = '\0';
    }
    for (int i = 0; i < num_ingredientes; i++)
    {
        printf("%d %s\n", i + 1, vetorStrings[i]);
    }

    fclose(arq);
}

void escolhe_listagem_ingrediente(FILE *arq){
    int opcao;

    if ((arq = fopen("Ingredientes.txt", "r")) == NULL)
    {
        printf("Impossivel abrir o arquivo em escolhe_listagem_ingrediente\n");
        exit(1);
    }

    printf("Escolha como deseja listar os ingredientes:\nAperte:\n1: por descricao\n2: por ordem de cadastro\n3: por ordem de codigo\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
    {
        listar_por_descricao(arq);
        break;
    }
    case 2:
    {
        listar_por_codigo(arq);
        break;
    }
    case 3:
    {
        listar_por_codigo(arq);
        break;
    }
    default:
    {
        printf("O numero escolhido e invalido.\n");
    }
    }
    fclose(arq);
}

void listar_receita_por_descricao(FILE *arq){
    int i, j, k;
    char *tmp;

    if ((arq = fopen("Receitas.txt", "r")) == NULL)
    {
        printf("Impossivel abrir o arquivo em listar_receita_por_descricao\n");
        exit(1);
    }

    int num_receitas = numero_receitas(arq);

    char **vetorStrings;

    if ((vetorStrings = (char **)malloc(sizeof(char *) * num_receitas)) == NULL)
    {
        printf("Erro alocacao de memoria em listar_por_receitas_descricao\n");
        exit(1);
    }

    for (i = 0; i < num_receitas; i++)
    {
        vetorStrings[i] = (char *)malloc(sizeof(char) * TAM_MAX_INGREDIENTE);
        if (vetorStrings[i] == NULL)
        {
            printf("Erro alocacao de memoria em listar_por_receitas_descricao\n");
            exit(1);
        }
    }

    for (i = 0; i < num_receitas; i++)
    {
        fgets(vetorStrings[i], TAM_MAX_RECEITA, arq);
        vetorStrings[i][strlen(vetorStrings[i]) - 1] = '\0';
    }

    for (i = 0; i < num_receitas - 1; i++)
    {
        for (j = 0; j < num_receitas - 1; j++)
        {
            // Se estiver fora de ordem...
            if (strcmp(vetorStrings[j], vetorStrings[j + 1]) > 0)
            {
                // ... troca de posicao
                tmp = vetorStrings[j];
                vetorStrings[j] = vetorStrings[j + 1];
                vetorStrings[j + 1] = tmp;
            }
        }
    }

    printf("Legenda:\nCodigo | Nome | [Ingrediente|Quantidade]\n");
    for (i = 0; i < num_receitas; i++)
    {
        fseek(arq, 0, SEEK_SET);

        for (k = 0; k < num_receitas; k++)
        {
            char texto[TAM_MAX_RECEITA];

            fgets(texto, TAM_MAX_RECEITA, arq);
            texto[strlen(texto) - 1] = '\0';

            if (strcmp(texto, vetorStrings[i]) == 0)
                printf("%d ", k + 1);
        }

        printf("%s\n", vetorStrings[i]);
    }

    for (i = 0; i < num_receitas; i++)
        free(vetorStrings[i]);

    free(vetorStrings);

    fclose(arq);
}

void listar_receita_por_codigo(FILE *arq){
    int i;

    arq = fopen("Receitas.txt", "r");

    int num_receitas = numero_receitas(arq);

    char vetorStrings[num_receitas][TAM_MAX_RECEITA];

    printf("Legenda: Codigo | Nome | [Ingrediente|Quantidade]\n");
    for (i = 0; i < num_receitas; i++)
    {
        fgets(vetorStrings[i], TAM_MAX_RECEITA, arq);
        if (vetorStrings[i][strlen(vetorStrings[i]) - 1] == '\n')
            vetorStrings[i][strlen(vetorStrings[i]) - 1] = '\0';
    }
    for (int i = 0; i < num_receitas; i++)
    {
        printf("%d %s\n", i + 1, vetorStrings[i]);
    }

    fclose(arq);
}

void escolhe_listagem_receita(FILE *arq){
    int opcao;

    arq = fopen("Ingredientes.txt", "r");

    printf("Escolha como deseja listar os ingredientes:\nAperte:\n1: por descricao\n2: por ordem de cadastro\n3: por ordem de codigo\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        listar_receita_por_descricao(arq);
        break;
    case 2:
        listar_receita_por_codigo(arq);
        break;
    case 3:
        listar_receita_por_codigo(arq);
        break;
    default:
        printf("O numero escolhido e invalido.\n");
    }
    fclose(arq);
}

void cadastrar_receita(FILE *arq){
    int aux, i;

    arq = fopen("Receitas.txt", "a+");
    if (arq == NULL)
    {
        printf("Impossivel abrir o arquivo em cadastrar_receita\n");
        exit(1);
    }

    receita proximo;

    proximo.nome_receita = (char *)calloc(TAM_MAX_RECEITA, sizeof(char));
    printf("Informe o nome da receita que queira cadastrar: \n");
    fflush(stdin);
    fgets(proximo.nome_receita, TAM_MAX_RECEITA, stdin);

    if (proximo.nome_receita[strlen(proximo.nome_receita) - 1] == '\n')
        proximo.nome_receita[strlen(proximo.nome_receita) - 1] = '\0';
    fprintf(arq, "%s ", proximo.nome_receita);

    printf("Quantos ingredientes serao usados na receita? \n");
    scanf("%d", &proximo.quantidade_ingredientes);

    proximo.ingredientes = (int *)calloc(proximo.quantidade_ingredientes, sizeof(int));
    proximo.quantidade_do_ingrediente = (int *)calloc(proximo.quantidade_ingredientes, sizeof(int));

    for (aux = 0; aux < proximo.quantidade_ingredientes; aux++)
    {
        printf("Digite o codigo do ingrediente %d: \n", aux + 1);
        fflush(stdin);
        scanf("%d", &proximo.ingredientes[aux]);
        printf("Digite a quantidade do ingrediente %d: \n", aux + 1);
        fflush(stdin);
        scanf("%d", &proximo.quantidade_do_ingrediente[aux]);

        fprintf(arq, "[%d/%d] ", proximo.ingredientes[aux], proximo.quantidade_do_ingrediente[aux]);
    }

    fputc('\n', arq);

    fclose(arq);
}

int main(int argc, char **argv){
    int j, r;
    int opcaomenu;

    FILE *arq_ingredientes;
    FILE *arq_receitas;

    do
    {
        printf("################### MENU ###################\n\nAperte:\n1 para ver os ingredientes\n2 para cadastrar novo ingrediente\n");
        printf("3 para ver as receita\n4 para cadastrar nova receita\n5 para encerrar o programa\n");
        (void)scanf("%d", &opcaomenu);
        switch (opcaomenu)
        {
        case 1:
        {
            escolhe_listagem_ingrediente(arq_ingredientes);
            break;
        }
        case 2:
        {
            cadastrar_ingrediente(arq_ingredientes);
            break;
        }
        case 3:
        {
            escolhe_listagem_receita(arq_receitas);
            break;
        }
        case 4:
        {
            cadastrar_receita(arq_receitas);
        }
        case 5:
        {
            break;
        }
        default:
        {
            printf("O numero escolhido e invalido.\n");
        }
        }
    } while (opcaomenu != 5);

    return SUCESSO;
}