#include "jogo.h"
// .c Contendo todas as definições de funções relacionadas a estrutura de Grafo.

// Código (número visual) do jogo
/*
    Visualização: 87654321
    -------------
    | 1 | 2 | 3 |
    -------------
    | 4 | 5 | 6 |
    -------------
    | 7 | 8 | 0 |
    -------------
*/
int obter_codigo(Grafos_mat *tabela)
{
    int codigo = 0, base_dez = 1;
    for(int i = 0; i < 9; i++)
    {
        codigo += tabela->adj[i][i] * base_dez;
        base_dez *= 10;
    }
    return codigo;
}

// Listas
void lista_libera(Lista *fonte)
{
    Lista *passo = fonte;
    while(passo != NULL)
    {
        Lista *buffer = passo->prox;
        free(passo);
        passo = buffer;
    }
    return;
}
Lista *lista_insere(Lista *fonte, Grafos_mat *valor)
{
    Lista *passo = (Lista *) calloc(1, sizeof(Lista));
	passo->grafo = aloca_grafo_m();
	grafo_copia(passo->grafo, valor);
	passo->valor = obter_codigo(valor);
	passo->prox = fonte;
    return passo;
}
int lista_procura(Lista* list, int alvo)
{
    Lista *passo;
    for(passo = list; passo != NULL; passo = passo->prox)
        if(passo->valor == alvo)
            return TRUE;
    return FALSE;
}

// Filas (lista++)
Fila *Fila_cria()
{
	Fila *novo = (Fila *) calloc(1, sizeof(Fila));
	novo->inicio = NULL, novo->fim = NULL;
	return novo;
}
void Fila_insere(Fila *fonte, Grafos_mat *info)
{
	Lista *inserir = (Lista *) malloc(sizeof(Lista));
	inserir->grafo = aloca_grafo_m();
	grafo_copia(inserir->grafo, info);
	inserir->prox = NULL;
	inserir->valor = 0;

	if(fonte->inicio == NULL)
	{	// Inserir primeiro
		fonte->inicio = inserir;
		fonte->fim = inserir;
	}
	else if(info->dist_global < fonte->inicio->grafo->dist_global)
	{	// Inserir na frente
		inserir->prox = fonte->inicio;
		fonte->inicio = inserir;
	}
	else for(Lista *passo = fonte->inicio; 1; passo = passo->prox)
		{
			if(passo->prox == NULL)
			{	// Inserir No Fim
				passo->prox = inserir;
				fonte->fim = inserir;
				break;
			}
			else if(passo->prox->grafo->dist_global > info->dist_global)
			{	// Inserir no meio
				inserir->prox = passo->prox;
				passo->prox = inserir;
				break;
			}
		}
	return;
}
Grafos_mat *Fila_retira(Fila *fonte)
{
	Grafos_mat *info = aloca_grafo_m(); //(Grafos_mat *) malloc(sizeof(Grafos_mat));
	if(fonte->inicio != NULL)
    {
        Lista *delete = fonte->inicio;
        grafo_copia(info, delete->grafo);
        fonte->inicio = delete->prox;
        
        if(fonte->inicio == NULL) // Se ficar vazio, marcar como fim
            fonte->fim = NULL;
		libera_grafo_m(delete->grafo);
        free(delete);
    }
    return info;	
}
void Fila_libera(Fila *fonte)
{
    lista_libera(fonte->inicio);
	return;
	// Lista *passo = fonte->inicio;
    // while(passo != NULL)
    // {
    //     Lista *buffer = passo->prox;
    //     libera_grafo_m(passo->grafo);
	// 	free(passo);
    //     passo = buffer;
    // }
    // free(fonte);
    // return;
}

// Grafos
// Aloca o grafo
Grafos_mat* aloca_grafo_m(void) {
	Grafos_mat* mat;

	mat = (Grafos_mat*)malloc(sizeof(Grafos_mat));
	
	mat->adj = (Bool**)malloc(sizeof(Bool*) * TAMANHO);
	
	for (int i = 0; i < TAMANHO; i++)
	{
		mat->adj[i] = (Bool*)calloc(TAMANHO, sizeof(Bool));
	}

	mat->arcos = 0;
	mat->vert = TAMANHO;
	mat->dist_global = INT32_MAX;
	mat->dist_local = INT32_MAX;
	mat->parente = NULL;

	return mat;
}
// Libera o grafo
void libera_grafo_m(Grafos_mat* mat) {

	for (int i = 0; i < mat->vert; i++) {
		free(mat->adj[i]);
	}
	free(mat->adj);
	free(mat);
	return;
}
// Copia um grafo para outro
void grafo_copia(Grafos_mat *dest, Grafos_mat *fonte)
{
	for(int i = 0; i < 9; i++)
		dest->adj[i][i] = fonte->adj[i][i];
	dest->arcos = fonte->arcos;
	dest->vert = fonte->vert;
	dest->dist_global = fonte->dist_global;
	dest->dist_local = fonte->dist_local;
	dest->parente = fonte->parente;
	return;
}
// Insere uma aresta não-orientada no grafo;
void insere_arco_m(Grafos_mat* mat, Vertice origem, Vertice destino) {

	if (mat->adj[origem][destino] == 0) {
		mat->adj[origem][destino] = 1;
		mat->adj[destino][origem] = 1;
		mat->arcos++;
	}
	return;
}
// Retira uma aresta do grafo;
void retira_arco_m(Grafos_mat* mat, Vertice origem, Vertice destino) {

	if (mat->adj[origem][destino] == 1) {
		mat->adj[origem][destino] = 0;
		mat->adj[destino][origem] = 0;
		mat->arcos--;
	}

}
