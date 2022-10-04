#define ERRO_1 -1
#define SUCESSO 0
#define TAMANHO 9
#define NUM_DE_EMBARALHAMENTOS 500

#define TRUE 1
#define FALSE 0
#define EXIT -1

typedef int Vertice;
typedef int Bool;

// Grafo de matriz de adjacência não-orientado;
typedef struct grafos_matriz_adj {

    Vertice vert;
    int arcos;
    Bool** adj;
    int dist_local;
    int dist_global;
    struct grafos_matriz_adj *parente;
}Grafos_mat;

Grafos_mat* aloca_grafo_m(void);
void grafo_copia(Grafos_mat *dest, Grafos_mat *fonte);
void libera_grafo_m(Grafos_mat* mat);
void insere_arco_m(Grafos_mat* mat, Vertice origem, Vertice destino);
void retira_arco_m(Grafos_mat* mat, Vertice origem, Vertice destino);
int obter_codigo(Grafos_mat *tabela);

// Lista encadeada & funções
typedef struct p_ListaEncad
{
    int valor;
    Grafos_mat *grafo;
    struct p_ListaEncad *prox;
} Lista;

Lista *lista_insere(Lista *fonte, Grafos_mat *info);
void lista_libera(Lista *fonte);
int lista_procura(Lista* list, int alvo);

// Fila & funções
typedef struct p_fila
{
    Lista *inicio;
    Lista *fim;
} Fila;

Grafos_mat *Fila_retira(Fila *fonte);
Fila *Fila_cria();
void Fila_insere(Fila *fonte, Grafos_mat *info);
void Fila_libera(Fila *fonte);