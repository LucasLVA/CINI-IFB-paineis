#include <ncurses.h>
#include <panel.h>
#include "struct.h"
#include "cliente.h"
#include "funcionario.h"
#include "funcoesgerais.h"
#include "principal.h"

#define NUM_SALAS 5
#define SIZE_NAME 100


int main(void) {
	
	/*Declaração das variaveis*/
	WINDOW *wins[3];
	PANEL *panels[3];
	dados_janela win1;
	cliente clientes[MAX_CLIENTE];
	int i, opcao = 0; /*Controla a movimentação dos cursores nos menus e informa as ação escolhida*/
	int tela = 0;/*Indice da tela a ser exibida*/
	int ch=0;/*Armazrna a tecla digitada*/
	int salas = 0;
	char filmes[NUM_SALAS][SIZE_NAME];
	char salas_cinema[NUM_SALAS][LETRAS][COLUNAS];
	int venda_ingressos = 0;
  


	/*Fim da declaração das variaveis*/

	/*Parametros de inicialização do ncurses*/
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);

	/*Inicialização dos pararemetros das variaveis e formatação das janelas e paineis*/
	int_parametros_win (&win1);
	criar_janelas(win1, wins);
	inicializa_matriz (filmes);
	inicializa_salas(salas_cinema);
	
	/*Cria os paineis associados as janelas*/
	for (i = 0; i <= 2; i++) {
    panels[i] = new_panel (wins[i]);  /* Move 0, ordem: stdscr-0-[i]-[i]*/
  }
	/*Cria bordas associadas as janelas*/
	criar_borda(wins);
	
	/*Programa comaça aqui!*/
	menu (wins, win1, opcao, panels);
	

	//Navega pelos menus
	while(opcao != -1){
		ch = getch();
		if (ch != 10){
			mvwprintw(wins[0], win1.cursor, win1.startx,"  ");
			opcao = escolhe_opcao(ch, opcao, &win1,2);
			mvwprintw(wins[0], win1.cursor, win1.startx,"->");
			update_panels();
			doupdate();
		}
		if(ch == 10){
			mvwprintw(wins[0], win1.cursor, win1.startx,"  ");
			win1.cursor = win1.starty+4; //zera o cursor
			menu (wins, win1, opcao+1, panels);
			switch(opcao){
				case 0:
					opcao = 0;
					menu_cliente(win1, wins[1], &salas,filmes,clientes,salas_cinema,&venda_ingressos);
					break;
				case 1:
					opcao = 0;
					menu_funcionario (win1, wins[2], &salas, filmes,salas_cinema, venda_ingressos, clientes);
					break;
				case 2:
					opcao = -1;
					break;
			}
			menu (wins, win1, 0, panels);
		}
		
	}
	
	refresh();
	endwin();
  
  
	//make clear && make all && ./main
  return 0;
}















