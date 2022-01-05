#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <ncurses.h>
#include <panel.h>
#include "struct.h"

void print_menu_cliente (WINDOW *wins, dados_janela win1);

void print_menu_consulta_cartaz (WINDOW *wins, dados_janela win1, char filmes[NUM_SALAS][SIZE_NAME],int salas_ocupadas);

int consulta_cartaz(char filmes[NUM_SALAS][SIZE_NAME], WINDOW *wins, dados_janela win1,int *salas,char salas_cinema[NUM_SALAS][LETRAS][COLUNAS]);

void verifica_filme_cartaz (WINDOW *wins, dados_janela win1, char filmes[NUM_SALAS][SIZE_NAME], int salas_ocupadas);

int checar_vagas(char sala_cinema[LETRAS][COLUNAS],int ingressos);

void bloqueia_covid(char sala_cinema[LETRAS][COLUNAS], int i, int j);

void escolhe_acento(char filme[SIZE_NAME],WINDOW *wins,dados_janela win1,cliente *cliente,char sala_cinema[LETRAS][COLUNAS]);

int compra_ingresso(char filmes[NUM_SALAS][SIZE_NAME], WINDOW *wins, dados_janela win1,cliente *clientes,char salas_cinema[NUM_SALAS][LETRAS][COLUNAS],int *salas);

void checar_ingresso(dados_janela win1, WINDOW *wins,char filmes[NUM_SALAS][SIZE_NAME], cliente clientes[MAX_CLIENTE],int *venda_ingressos,int vendeu);

void menu_cliente (dados_janela win1, WINDOW *wins, int *salas, char filmes[NUM_SALAS][SIZE_NAME], cliente clientes[MAX_CLIENTE], char salas_cinema[NUM_SALAS][LETRAS][COLUNAS], int *venda_ingressos);



#endif