#ifndef FUNCOESGERAIS_H
#define FUNCOESGERAIS_H

#include <stdio.h>
#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"

void inicializa_matriz (char filmes[NUM_SALAS][SIZE_NAME]);

void inicializa_salas (char salas_cinema[NUM_SALAS][LETRAS][COLUNAS]);

void print_salas(char sala_cinema[LETRAS][COLUNAS], WINDOW *wins, int posicaoy,int posicaox);

void int_parametros_win (dados_janela *win1);

void criar_janelas (dados_janela win1, WINDOW **wins);

void criar_borda(WINDOW **wins);

int escolhe_opcao(int ch,int opcao, dados_janela *win1, int qtdOpcao);

void imprime_alerta(WINDOW *wins,dados_janela win1, char mensagem[500]);

#endif