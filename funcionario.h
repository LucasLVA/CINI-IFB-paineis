#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <panel.h>
#include "struct.h"

void print_menu_funcionario (WINDOW *wins, dados_janela win1);

void print_menu_salas (WINDOW *wins, dados_janela win1, char filmes[NUM_SALAS][SIZE_NAME], int salas_ocupadas);

void print_menu_remove_filme (WINDOW *wins, dados_janela win1, char filmes[NUM_SALAS][SIZE_NAME], int salas_ocupadas);

void cadastrar_filme(int *salas, char filmes[NUM_SALAS][SIZE_NAME], WINDOW *wins, dados_janela win1, int ch);

void remove_filme(char filmes[NUM_SALAS][SIZE_NAME], WINDOW *wins, dados_janela win1,int *salas);

void menu_salas (dados_janela win1, WINDOW *wins, int *salas, char filmes[NUM_SALAS][SIZE_NAME],char salas_cinema[NUM_SALAS][LETRAS][COLUNAS], int venda_ingressos, cliente clientes[MAX_CLIENTE]);

void visualizar_sala(int salas, dados_janela win1,WINDOW *wins,char filmes[NUM_SALAS][SIZE_NAME]);

void menu_funcionario (dados_janela win1, WINDOW *wins, int *salas, char filmes[NUM_SALAS][SIZE_NAME],char salas_cinema[NUM_SALAS][LETRAS][COLUNAS], int venda_ingressos, cliente clientes[MAX_CLIENTE]);



#endif