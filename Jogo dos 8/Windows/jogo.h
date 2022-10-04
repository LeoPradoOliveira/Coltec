// Inclusões com dependencia
#ifdef _WIN32
#include <Windows.h>
#elif __unix__
#include <unistd.h>
#endif

// Inclusões gerais
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

// Direção
typedef enum p_Direc
{
    Cima = 0,
    Direita = 1,
    Baixo = 2,
    Esquerda = 3
} Direcao;

// Funções dependentes do SO
void esperar(unsigned int milisecs);
void limpar_tela();
void imprime_linhaVazia();
void imprime_jogo(Grafos_mat* grafo_jogo);
void imprime_incio();
void imprime_fim(int movimentos, int tempo);

// Busca em grafo via A*
void fazer_movimento(Grafos_mat *jogo, Direcao direc);
int distancia_Manhattan(Grafos_mat *jogo);
int obter_lugar(Grafos_mat *jogo, int valor);
Grafos_mat *jogo_resolver_A(Grafos_mat *jogo);

// Jogo
Grafos_mat* matriz_referencia(void);
Grafos_mat* matriz_embaralhada(void);
Grafos_mat* jogo_impossivel_exemplo(void);
void mostrar_resolvido(Grafos_mat *grafo_jogo);
void inicia_jogo(void);
int possivel_resolver(Grafos_mat* grafo_jogo);
int verifica_se_acabou(Grafos_mat* grafo_jogo);
int faz_jogada(Grafos_mat *grafo_jogo);
