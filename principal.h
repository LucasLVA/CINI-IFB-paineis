#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <stdio.h>
#include "cliente.h"
#include "funcionario.h"
#include <ncurses.h>
#include <panel.h>
#include "struct.h"

void print_menu_principal (WINDOW *wins, dados_janela win1);

void menu(WINDOW *wins[3], dados_janela win1,int opcao,PANEL *panels[3]);

#endif